const express = require('express');
const app = express();

const port = 8080;
app.use(express.static('public'));

// Start
const server = app.listen(port, () => {    
    const host = server.address().address;
    const port = server.address().port;
    console.log('running at http://' + (host === '::' ? 'localhost' : host) + ':' + port)
});