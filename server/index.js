const express = require('express');
const app = express();
const cors = require('cors');

app.use(express.json());
app.use(cors());

let db = [];

function addValue(value) {
  let currentTime = new Date();
  currentTime = `${currentTime
    .getMinutes()
    .toString()
    .padStart(2, '0')}:${currentTime.getSeconds().toString().padStart(2, '0')}`;
  db.push({ timestamp: currentTime, value: value });
}

app.get('/', (req, res) => {
  res.json(db);
});

app.post('/', (req, res) => {
  console.log('Got something');
  addValue(req.body.value);
  res.json({ message: 'Value added' });
});

app.listen(3000, () => {
  console.log('Server running on port 8080');
});
