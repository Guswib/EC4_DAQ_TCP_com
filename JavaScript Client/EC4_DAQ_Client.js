// Include Nodejs' net module.
const Net = require('net');
// The port number and hostname of the server.
const port = 3364;
const host = '127.0.0.1';

// Create a new TCP client.
const client = new Net.Socket();
// Send a connection request to the server.
client.connect({ port: port, host: host }, function() {
    // If there is no error, the server has accepted the request and created a new 
    // socket dedicated to us.
    console.log('TCP connection established with the server.');

    // The client can now send data to the server by writing to its socket.
    console.log('Send: echo');
    client.write('echo\r\n');
    console.log('Send: state');
    client.write('state\r\n');
    console.log('Send: irange');

    client.write('irange\r\n');
    console.log('Send: echo');
    client.write('state\r\n');
    console.log('Send: ping');
    client.write('echo\r\n');
    client.write('Eset=1.2V\r\n');
    console.log('done');
    
});

// The client can also receive data from the server by reading from its socket.
client.on('data', function(chunk) {
    console.log(`Data received from the server:\n${chunk.toString()}.`);
    
    // Request an end to the connection after the data has been received.
    client.end();
});

client.on('end', function() {
    console.log('Requested an end to the TCP connection');
});