const WebSocket = require('ws');
const server = new WebSocket.Server({ port: 8080 });
const express = require('express');
const app = express();
const cors = require('cors');

app.use(express.json());
app.use(cors());

let db = [];

function addValue(value) {
    let currentTime = new Date();
    currentTime = `${currentTime.getMinutes().toString().padStart(2, '0')}:${currentTime.getSeconds().toString().padStart(2, '0')}`;
    db.push({ timestamp: currentTime, value: value });
}

addValue(Math.floor(Math.random() * 30));

server.on('connection', function (ws) {
    console.log('New device connected');

    ws.on('message', function (data) {
        try {
            const sensorData = JSON.parse(data);
            console.log('Received sensor data:', sensorData);
            addValue(sensorData.value);
        } catch (error) {
            console.error('Error processing message:', error);
        }
    });

    ws.on('close', function () {
        console.log('Device disconnected');
    });
});

app.get('/', (req, res) => {
    res.json(db);
});

app.listen(3000, () => {
    console.log('Server running on port 3000');
});

console.log('WebSocket server running on port 8080');
