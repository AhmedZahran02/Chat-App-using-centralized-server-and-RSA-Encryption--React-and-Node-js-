const WebSocket = require("ws");
const wss = new WebSocket.Server({ port: 8082 });

let clients = new Map(); 

let addConnection = (username, e, n) => {
  if (clients.has(username)) {
    return false;
  } else {
    clients.set(username, [e, n]); 
    console.log(clients.get(username));
    return true;
  }
}; 

let getKey = (username) => {
  if (clients.has(username)) 
  { 
    return true;
  } else {
    return false;
  }
};
 
wss.on("connection", (ws) => { 
  ws.on("message", (data) => 
  {
    console.log(data);
    data = JSON.parse(data);
    if (data.type === "connection") 
    {
      const { username, e, n } = data;
      if (addConnection(username, e, n)) {
        console.log("New Client");
        ws.send(JSON.stringify({ type: "connection", code: "200" }));
        
        ws.on("close",(c,r)=>{
          clients.delete(username);
          console.log(`deleted username : ${username}`);
        }) 
      } else {
        console.log("Old Client");
        ws.send(JSON.stringify({ type: "connection", code: "404" }));
      }

   

    } 
    else if (data.type === "getKey") 
    {
      const { username } = data;
      if (getKey(username)) 
      {
        let e, n;
        [e, n] = clients.get(username);
        ws.send 
        (
          JSON.stringify
          ({
            type: "key",
            username: username,
            e: e,
            n: n,
          })
        );
      } 
      else 
      {
        console.log("No Client Found");
        ws.send(JSON.stringify({username:null}));
      }
    } 
    else if (data.type === "msg") 
    {
      const { username1, username2, msg } = data;
      wss.clients.forEach(function (client) 
      {
        client.send(
          JSON.stringify 
          ({
            type: "msg",
            username: username2,
            username2: username1,
            msg: msg, 
          })
        );
      });
    }
  });
});
