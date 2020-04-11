from websocket_server import WebsocketServer
from random import randint
import json
import time

networks = [
	{"SSID":"454csdf",		"RSSI":"-12",	"CH":1,		"AUTH":3},
	{"SSID":"router_45tsf", "RSSI":"-78",	"CH":2,		"AUTH":2},
	{"SSID":"wqesdf",		"RSSI":"-21",	"CH":12,	"AUTH":2},
	{"SSID":"iphone2323",	"RSSI":"-34",	"CH":4,		"AUTH":1},
	{"SSID":"netgear3324",	"RSSI":"-14",	"CH":6,		"AUTH":0},
	{"SSID":"454csdf",		"RSSI":"-12",	"CH":1,		"AUTH":3},
	{"SSID":"router_45tsf", "RSSI":"-78",	"CH":2,		"AUTH":2},
	{"SSID":"wqesdf",		"RSSI":"-21",	"CH":12,	"AUTH":2},
	{"SSID":"iphone2323",	"RSSI":"-34",	"CH":4,		"AUTH":1},
	{"SSID":"netgear3324",	"RSSI":"-14",	"CH":6,		"AUTH":0}]

filesystem = [
	{"File":"index.html",	"Size":"12032"},
	{"File":"main.js", 		"Size":"78233"},
	{"File":"style.css",	"Size":"21232"},
	{"File":"w3.css",		"Size":"34323"},
	{"File":"iconify.js",	"Size":"14232"}]
# Called for every client connecting (after handshake)
def new_client(client, server):
	server.send_message_to_all("New client connected: id_%d" % client['id'])
	print("New client connected: id_%d" % client['id'])


# Called for every client disconnecting
def client_left(client, server):
	server.send_message_to_all("Client(%d) disconnected" % client['id'])
	print("Client(%d) disconnected" % client['id'])

# Called when a client sends a message
def message_received(client, server, message):
	#server.send_message_to_all("Client(%d) said: %s" % (client['id'], message))
	print("Client(%d) said: %s" % (client['id'], message))
	#time.sleep(5)

	reply_message = {
		  "type" : 0,
		  "value": 0,
		}

	try:
		request_message = json.loads(message)

	except:
		err = "error: bad json request"
		reply_message["value"] = err
		print(err)

	else:
		if isinstance(request_message, dict) and "type" in request_message:

			cmd = request_message["type"]
			reply_message["type"] = cmd;

			if   (cmd == 0):
				#server.send_message(client['id'], "pong")
				reply_message["value"] = "pong"

			
			elif (cmd == 1):
				#server.send_message(client['id'], "pong")
				reply_message["value"] = randint(10000, 99999)

			
			elif (cmd == 2):
				reply_message["value"] = [{
					  "battery":randint(0, 100),
					  "memory": randint(0, 100),
					  "storage": randint(0, 100),
					}]
			
			elif (cmd == 3):
				reply_message["value"] = networks

			elif (cmd == 4):
				reply_message["value"] = filesystem

			elif (cmd == 5):
				
				with open("received_file.dat", "w+") as file:
					file.write(request_message["value"])
					file.close()
				reply_message["value"] = True

		else:
			err = "error: unknown json request"
			reply_message["value"] = err
			print(err)	

	server.send_message_to_all(json.dumps(reply_message));

PORT=81
server = WebsocketServer(PORT)
if isinstance(server, WebsocketServer):
	server.set_fn_new_client(new_client)
	server.set_fn_client_left(client_left)
	server.set_fn_message_received(message_received)
	server.run_forever()
else:
	print("failed open websocket.")