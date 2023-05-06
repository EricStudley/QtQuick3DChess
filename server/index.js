'use strict';

Set.prototype.find = function(cb) {
    for (const e of this) {
        if (cb(e)) {
            return e;
        }
    }
}

var _generateUUID = function () {
    return uuid.v4()
}

import jsChessEngine from 'js-chess-engine'
import _ from 'lodash'
import fs from 'fs'
import uuid from 'node-uuid'
import WebSocket, { WebSocketServer } from 'ws';

var wss = new WebSocketServer({ port: 9001 }),
runningServerList = {},
openServerList = {}

var createServer = function (ws, serverName) {
    ws.serverUuid = _generateUUID()

    openServerList[serverName] = {
        serverUuid: ws.serverUuid,
        players: [ws.uuid]
    }
}

var joinServer = function (ws, serverName) {
    var server = _.cloneDeep(openServerList[serverName]),
    serverInfo = {
        serverUuid: server.serverUuid,
        gameClient: new jsChessEngine.Game()
    }

    delete openServerList[serverName]

    runningServerList[serverInfo.serverUuid] = serverInfo

    ws.serverUuid = serverInfo.serverUuid
}

var addPlayerToGameQueue = function (uuid, ws, serverUuid) {

    if (_.isEmpty(openServerList)) {
        var serverUuid = _.isString(serverUuid) ? serverUuid : _generateUUID()

        ws.serverUuid = serverUuid
        ws.send(JSON.stringify({
                                   info: {
                                       uuid: uuid
                                   }
                               }))

        openServerList = {
            serverUuid: serverUuid,
            players: [uuid]
        }
    }
    else {
        openServerList.players.push(uuid)

        if (openServerList.players.length >= MAX_PLAYERS) {
            console.log('There are ' + MAX_PLAYERS + ' people waiting to play. Starting game.')

            var gameInfo = _.cloneDeep(openServerList),
            infoToReturn = {
                serverUuid: gameInfo.serverUuid,
                game_client: new jsChessEngine.Game()
            }

            openServerList = { }

            runningServerList[infoToReturn.serverUuid] = infoToReturn

            ws.serverUuid = infoToReturn.serverUuid // set the websocket.serverUuid so what we can loop through all of our websockets, look at the socket.serverUuid then know to send them that exact game
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

                if (_.has(runningServerList, ws.serverUuid)) {
                    var game = runningServerList[ws.serverUuid],
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
                case "createServer":
                    if (!ws.already_joined) {
                        ws.already_joined = true
                        createServer(ws, obj.serverName)
                    }
                    break
                case "joinServer":
                    if (!ws.already_joined) {
                        ws.already_joined = true
                        joinServer(ws, obj.serverName)
                    }
                    break
                case "sendServerList":
                    ws.send(JSON.stringify({
                                               serverList: Object.keys(openServerList)
                                           }))
                    break
                case "join":
                    if (!ws.already_joined) {
                        ws.already_joined = true
                        addPlayerToGameQueue(ws.uuid, ws, obj.serverUuid)
                    }
                    break
                }
            }

            wss.clients.forEach(function (socket) {
                var game = runningServerList[socket.serverUuid]

                if (game) {
                    var gameClient = game.game_client,
                    gameStatus = gameClient.exportJson()

                    socket.send(JSON.stringify({
                                                   objects: gameStatus,
                                                   serverList: Object.keys(openServerList)
                                               }))
                }
            })
        }
        catch (e) {
            console.log(e)
        }
    })
})
