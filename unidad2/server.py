from ast import Try
from http.server import BaseHTTPRequestHandler, HTTPServer
import json

#inicializamos el contador en 10

contador = 10

#response establece la respuesta HTTP el código 200 éxito
class MyHTTPRequestHandler(BaseHTTPRequestHandler):
    def _set_response(self, content_type="text/plain"):
        self.send_response(200)
        self.send_header("Content-type", content_type)
        self.end_headers()

    def throw_cusom_error(self, message):
        self._set_response("Application/json")
        self.wfile.write(json.dumps({"message": message}).encode())
    

    def do_GET(self):
        self._set_response()
        respuesta = "El valor es: " + str(contador)
        self.wfile.write(respuesta.encode())

    def do_POST(self):
        content_length = int(self.headers["Content-Length"])
        post_data = self.rfile.read(content_length)

        try:
            body_json = json.loads(post_data.decode())
        except:
           self.throw_cusom_error("Invalid JSON")
           return
          

        global contador

        # Check if action and quantity are present
        if (body_json.get('action') is None or body_json.get('quantity') is None):
           self.throw_cusom_error("Invalid JSON")
           return
        
        # Check if action is valid 
        if (body_json.get('action') != 'asc' and body_json('action') != 'desc'):
            self.throw_cusom_error("Invalid action")
            return
        #check if quantity is valid , integer 
        try:
            int(body_json['quantity'])
        except:
            self.throw_cusom_error("Invalid quantity")
            return

        if 'action' in body_json and 'value' in body_json:
            action = body_json['action']
            value = body_json['value']
            
            if action == 'asc':
                contador += value
            elif action == 'desc':
                contador -= value
        # Respond to the client
        response_data = json.dumps({"message": "Received POST data, new value: " + str(contador),
        "status": "OK"})
        self._set_response("application/json")
        self.wfile.write(response_data.encode())

        # Print the complete HTTP request
        print("\n----- Incoming POST Request -----")
        print(f"Requestline: {self.requestline}")
        print(f"Headers:\n{self.headers}")
        print(f"Body:\n{post_data.decode()}")
        print("-------------------------------")

        # Respond to the client
        response_data = json.dumps({"message": "Received POST data", "data": post_data.decode()})
        self._set_response("application/json")
        self.wfile.write(response_data.encode())


#conexión con visual studio code y postman 

def run_server(server_class=HTTPServer, handler_class=MyHTTPRequestHandler, port=7800):
    server_address = ("", port)
    httpd = server_class(server_address, handler_class)
    print(f"Starting server on port {port}...")
    httpd.serve_forever()

if __name__ == "__main__":
    run_server()