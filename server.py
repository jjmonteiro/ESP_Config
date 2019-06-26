from websocket_server import WebsocketServer
from random import randint
import json


networks = [
	{"SSID":"454csdf",		"RSSI":"-12",	"CH":1,		"AUTH":3},
	{"SSID":"router_45tsf", "RSSI":"-78",	"CH":2,		"AUTH":2},
	{"SSID":"wqesdf",		"RSSI":"-21",	"CH":12,	"AUTH":2},
	{"SSID":"iphone2323",	"RSSI":"-34",	"CH":4,		"AUTH":1},
	{"SSID":"netgear3324",	"RSSI":"-14",	"CH":6,		"AUTH":0}]

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

	try:
		obj = json.loads(message)
	except:
		print("error: bad json request")
	else:
		if isinstance(obj, dict) and "type" in obj:

			cmd = obj["type"]
			x = {
				  "type" : cmd,
				  "value": 0,
				}

			if (cmd == 0):
				#server.send_message(client['id'], "pong")
				x = {
					  "type" : cmd,
					  "value": "pong"
					}

			
			elif (cmd == 1):
				#server.send_message(client['id'], "pong")
				x = {
					  "type" : cmd,
					  "value": randint(10000, 99999)
					}
			
			elif (cmd == 2):
				x = {
					  "type" : cmd,
					  "name": "John",
					  "age": 30,
					  "married": True,
					  "divorced": False,
					  "children": ("Ann","Billy"),
					  "pets": None,
					  "cars": [
					    {"model": "BMW 230", "mpg": 27.5},
					    {"model": "Ford Edge", "mpg": 24.1}
					  ]
					}
			
			elif (cmd == 3):
				x = {
					  "type" : cmd,
					  "value": networks
				}

		server.send_message_to_all(json.dumps(x));

PORT=81
server = WebsocketServer(PORT)
server.set_fn_new_client(new_client)
server.set_fn_client_left(client_left)
server.set_fn_message_received(message_received)
server.run_forever()
