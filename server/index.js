'use strict';

var _generateUUID = function () {
    return uuid.v4()
}

import jsChessEngine from 'js-chess-engine'
import _ from 'lodash'
import fs from 'fs'
import uuid from 'node-uuid'
import WebSocket, { WebSocketServer } from 'ws';

var wss = new WebSocketServer({ port: 9001 }),
games = {},
gamesWaitingForPlayers = {},
MAX_PLAYERS = 2 // static for now but can easily change..

var addPlayerToGameQueue = function (uuid, ws, game_id) {

    if (_.isEmpty(gamesWaitingForPlayers)) {
        var game_id = _.isString(game_id) ? game_id : _generateUUID()

        ws.game_id = game_id
        ws.send(JSON.stringify({
                                   info: {
                                       uuid: uuid
                                   }
                               }))

        gamesWaitingForPlayers = {
            game_id: game_id,
            players: [uuid]
        }
    }
    else { // other players are also waiting to join a game on this map
        gamesWaitingForPlayers.players.push(uuid)

        if (gamesWaitingForPlayers.players.length >= MAX_PLAYERS) {
            console.log('There are ' + MAX_PLAYERS + ' people waiting to play. Starting game.')

            var gameInfo = _.cloneDeep(gamesWaitingForPlayers),
            infoToReturn = {
                game_id: gameInfo.game_id,
                game_client: new jsChessEngine.Game()
            }

            gamesWaitingForPlayers = { }

            games[infoToReturn.game_id] = infoToReturn

            ws.game_id = infoToReturn.game_id // set the websocket.game_id so what we can loop through all of our websockets, look at the socket.game_id then know to send them that exact game
        }
    }
}

wss.on('connection', function (ws) {
    ws.uuid = _generateUUID()
    ws.already_joined = false // only add them to a game once.. worry about disconnect or w/e later on..

    ws.on('message', function (message) {
        console.log("Message from socket with uuid", ws.uuid, ":/n", JSON.stringify(message))

        try {
            var obj = JSON.parse(message)

            console.log(obj)

            if (_.has(obj, 'move')) {

                if (_.has(games, ws.game_id)) {
                    var game = games[ws.game_id],
                    gameClient = game.game_client

                    gameClient.move(obj.move.from, obj.move.to)

                    var gameStatus = gameClient.exportJson()

                    ws.send(JSON.stringify({
                                               objects: gameStatus
                                           }))
                }
            }

            if (_.has(obj, 'command')) {

                switch (obj.command) {
                case "join":
                    if (!ws.already_joined) {
                        ws.already_joined = true
                        addPlayerToGameQueue(ws.uuid, ws, obj.game_id) // pass in ws so that we can set ws.game_id once that is determined.. this is kind of a hack but I see no harm :)
                    }
                    break
                case "start":
                    if (_.has(games, ws.game_id)) {
                        var game = games[ws.game_id],
                        gameClient = game.game_client,
                        gameStatus = gameClient.exportJson()

                        ws.send(JSON.stringify({
                                                   objects: gameStatus
                                               }))
                    }
                    break
                }
            }

            wss.clients.forEach(function (socket) {
                var game = games[socket.game_id]

                if (game) {
                    var gameClient = game.game_client,
                    gameStatus = gameClient.exportJson()

                    try {
                        socket.send(JSON.stringify({
                                                       objects: gameStatus
                                                   }))
                    }
                    catch (err) {
                        console.log(e)
                    }
                }
            })
        }
        catch (e) {
            console.log(e)
        }
    })
})
