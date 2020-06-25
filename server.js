const express = require('express');
const showdown = require('showdown');
const fs = require("fs");

const app = express();

const port = 8080;
app.use(express.static('public'));

// Start
const server = app.listen(port, () => {
    const host = server.address().address;
    const port = server.address().port;
    console.log('running at http://' + (host === '::' ? 'localhost' : host) + ':' + port)
});

// Routes
app.get('/markdownAsHtml', (req, res) => {
    const converter = new showdown.Converter();
    var path = __dirname + '/README.md';
    var markdown = fs.readFileSync(path, 'utf8');
    const html = converter.makeHtml(markdown);
    res.send(html);
});