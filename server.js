const express = require("express");
const app = express();

const PORT = 8080;


app.get("/apple",(req , res)=>{
    res.send("Hello");
    console.log("hello world");
})

app.post("/:name/:age", (req , res)=>{
    const {name , age} = req.params;
    res.send(`My name is ${name} and my age is ${age}`);
})

app.post("/search" , (req , res)=>{
    let data = req.query;
    res.send(data);
})

app.listen(PORT , ()=>{
    console.log(`server is running of port Localhost ${PORT}`);
})