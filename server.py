from websocket_server import WebsocketServer
from random import randint


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

	server.send_message_to_all('0')	

	if (message != '0'):
		print("Client(%d) said: %s" % (client['id'], message))

		if (message == "s1"):
			#server.send_message(client['id'], "pong")
			nr = randint(10, 99)
			server.send_message_to_all('{"type":'+str(nr)+ ', "value":'+str(nr*5)+'}');

		if (message == "s2"):
			server.send_message_to_all('{"type":22, "value":43423}');



PORT=81
server = WebsocketServer(PORT)
server.set_fn_new_client(new_client)
server.set_fn_client_left(client_left)
server.set_fn_message_received(message_received)
server.run_forever()
