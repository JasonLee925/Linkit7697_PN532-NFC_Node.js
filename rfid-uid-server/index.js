const express = require('express');
const app = express(); //建立一個Express伺服器

var fs = require('fs');
var file = "./data.json";
var data = JSON.parse(fs.readFileSync(file));


app.get('/rfid/:uid', (req, res) => {
    var input_uid = req.params.uid;
    
    if (data.uid.indexOf(input_uid) != -1){
        console.log("#" + input_uid + " 存在於資料庫中");
        res.send("y");
    }
    else{
        console.log("#" + input_uid + " 不存在資料庫中");
        res.send("n");
    }
});

app.listen(3005, () => {
    console.log('Running on port 3005!');
});
