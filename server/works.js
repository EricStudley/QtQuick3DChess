'use strict';

import jsChessEngine from 'js-chess-engine'
import _ from 'lodash'
import fs from 'fs'
import uuid from 'node-uuid'
import WebSocket, { WebSocketServer } from 'ws';

var wss = new WebSocketServer({ port: 9001 }),
runningServerList = {},
openServerList = {}

var createServer = function (ws, serverName) {
    ws.serverUuid = uuid.v4()
    openServerList[serverName] = ws.serverUuid
}

var joinServer = function (ws, serverName) {
    var serverUuid = openServerList[serverName]
    runningServerList[serverUuid] = new jsChessEngine.Game()
    ws.serverUuid = serverUuid

    delete openServerList[serverName]
}

wss.on('connection', function (ws) {
    ws.uuid = uuid.v4()
    ws.already_joined = false // only add them to a game once.. worry about disconnect or w/e later on..

    ws.on('message', function (message) {
        console.log("Message from socket with uuid", ws.uuid, ":/n", JSON.stringify(message))

        try {
            var obj = JSON.parse(message)

            console.log(obj)

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


                        wss.clients.forEach(function (ws) {
                            var gameClient = runningServerList[ws.serverUuid]

                            if (gameClient) {
                                var gameStatus = gameClient.exportJson()

                                if (gameStatus) {
                                    ws.send(JSON.stringify({
                                                               objects: gameStatus,
                                                               serverList: Object.keys(openServerList)
                                                           }))
                                }
                            }
                        })
                    }
                    break
                case "sendServerList":
                    ws.send(JSON.stringify({
                                               serverList: Object.keys(openServerList)
                                           }))
                    break
                }
            }

            //            wss.clients.forEach(function (socket) {
            //                var game = runningServerList[socket.serverUuid]

            //                if (game) {
            //                    var gameClient = game.game_client,
            //                    gameStatus = gameClient.exportJson()

            //                    socket.send(JSON.stringify({
            //                                                   objects: gameStatus,
            //                                                   serverList: Object.keys(openServerList)
            //                                               }))
            //                }
            //            })
        }
        catch (e) {
            console.log(e)
        }
    })
})
