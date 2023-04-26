'use strict';

var _generateUUID = function () {
    return uuid.v4()
}

import chess from 'chess'
import _ from 'lodash'
import fs from 'fs'
import uuid from 'node-uuid'
import WebSocket, { WebSocketServer } from 'ws';

var wss = new WebSocketServer({ port: 9001 }),
games = {},
gamesWaitingForPlayers = {},
GAME_TICK_LENGTH = 200, //ms
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
            players: [uuid],
        }
    }
    else { // other players are also waiting to join a game on this map
        gamesWaitingForPlayers.players.push(uuid)

        if (gamesWaitingForPlayers.players.length >= MAX_PLAYERS) {
            console.log('There are ' + MAX_PLAYERS + ' people waiting to play. Starting game.')

            var gameInfo = _.cloneDeep(gamesWaitingForPlayers),
            infoToReturn = {
                game_id: gameInfo.game_id
            }

            games[infoToReturn.game_id] = infoToReturn

            ws.game_id = infoToReturn.game_id // set the websocket.game_id so what we can loop through all of our websockets, look at the socket.game_id then know to send them that exact game
        }
    }
}


// Loop through ever websock and send the game info
// This is the loop where we will be updating players positions..
setInterval(function () {

    // Loop through games and update player/ghost positions
    _.forEach(games, function (game) {

    })

    if (!_.isEmpty(games)) {

        wss.clients.forEach(function (socket) {
            var game = games[socket.game_id]

            try {
                socket.send(JSON.stringify({
                                               objects: game,
                                               uuid: socket.uuid
                                           }))
            }
            catch (err) {
                // TODO what does this mean.. should we remove the player or something..
            }
        })
    }
}, GAME_TICK_LENGTH)

wss.on('connection', function (ws) {
    ws.uuid = _generateUUID()
    ws.already_joined = false // only add them to a game once.. worry about disconnect or w/e later on..

    ws.on('message', function (message) {
        console.log("Message from socket with uuid", ws.uuid, ":/n", JSON.stringify(message))

        try {
            var obj = JSON.parse(message)

            if (_.has(obj, 'command')) {

                switch (obj.command) {
                case "join":
                    if (!ws.already_joined) {
                        ws.already_joined = true
                        addPlayerToGameQueue(ws.uuid, ws, obj.game_id) // pass in ws so that we can set ws.game_id once that is determined.. this is kind of a hack but I see no harm :)
                    }
                    break
//                case "list":
//                    var serverInfo = _.mapValues(games, function (gameObj) {
//                        return {
//                            game_id: gameObj.game_id,
//                            map_name: gameObj.map_name,
//                            number_of_players: _.keys(gameObj.players).length
//                        }
//                    })

//                    ws.send(JSON.stringify({ info: serverInfo }))
//                    break
                default:
                    if (_.has(games, ws.game_id)) {
                        var game = games[ws.game_id],
                        player = game.players[ws.uuid]

                        player.requestedDirection = parseInt(obj.command)
                    }
                    break
                }
            }
        }
        catch (e) {
            console.log(e)
        }
    })
})
