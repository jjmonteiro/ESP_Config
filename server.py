from websocket_server import WebsocketServer
from random import randint
import json
import time

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
	time.sleep(5)

	x = {
		  "type" : 0,
		  "value": 0,
		}

	try:
		obj = json.loads(message)

	except:
		err = "error: bad json request"
		x["value"] = err
		print(err)

	else:
		if isinstance(obj, dict) and "type" in obj:

			cmd = obj["type"]


			if (cmd == 0):
				#server.send_message(client['id'], "pong")
				x["value"] = "pong"

			
			elif (cmd == 1):
				#server.send_message(client['id'], "pong")
				x["value"] = randint(10000, 99999)

			
			elif (cmd == 2):
				x["value"] = [{
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
					}]
			
			elif (cmd == 3):
				x["value"] = networks
		else:
			err = "error: unknown json request"
			x["value"] = err
			print(err)	

	server.send_message_to_all(json.dumps(x));

PORT=81
server = WebsocketServer(PORT)
server.set_fn_new_client(new_client)
server.set_fn_client_left(client_left)
server.set_fn_message_received(message_received)
server.run_forever()
