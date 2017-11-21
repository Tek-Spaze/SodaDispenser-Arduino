var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var SerialPort = require('serialport');
var port = new SerialPort('/dev/ttyACM3',{baudRate: 115200}, function (err) {
	if (err) {
		return console.log('Error: ', err.message);
	}
});
 
app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function(socket){
  console.log("User connected");
  socket.on('chat message', function(msg){
    console.log(msg);
    io.emit("chat message", msg);
    port.write(msg);
  });

});

http.listen(3000, function(){
  console.log('listening on *:3000');
});
