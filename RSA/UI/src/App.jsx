import './App.css';
import { Navigate, useNavigate } from 'react-router-dom';

function App() {

  let Nav = useNavigate();

  let Crypto = require('./math');
  let crypt = new Crypto();

  let username = "";
  let p = "";
  let q = "";
  let e = "";
  let n = "";
  let d = "";


  const ws = new WebSocket("ws://localhost:8082");

  ws.addEventListener("message",(message)=>
  {
    let data = JSON.parse(message.data);
    if (data.type === "connection")
    {
      if(data?.code === "200"){
        Nav("/chat",{state:{data:{username:username,d:d,n:n}}})
      }else{
        window.alert(`the username ${username} already used please try different one !!`);
      }
    }
  });

  const isPrime = (num)=>
  {
    if(num <= 1) return false;
    for (let i = 2; i*i <= num; i++)
    {
      if (num % i === 0)
        return false;
    }
    return true;
  }

  const connectToServer = ()=>
  {
    if (username.length === 0)
    {
      alert("username is empty...");
      return;
    }

    const primeCondition = isPrime(p) && isPrime(q);
    const coversRange = (p * q) > 128;

    if (!primeCondition || !coversRange || p<0 || q<0)
    {
      alert("p or q is invalid... please try again");
      return;
    }

    [e,n,d] = crypt.generateKey(p,q);
    ws.send(JSON.stringify({type:"connection",username: username, e: e, n: n}));
  }

  return (
    <div className="App">

      <div className="login">
        <h1 className='appTitle'>
          MOAOZ
        </h1>

        <div className="inputContainer">
          <label htmlFor="Username" className='lbl'>Username</label>
          <input type="text" name="Username" id="Username" onChange={(e)=>{username = e.target.value}}/>
        </div>

        <div className="inputContainer">
          <label htmlFor="P" className='lbl'>P</label>
          <input type="number" name="P" id="P" onChange={(e)=>{p = e.target.value}}/>
        </div>        
        <div className="inputContainer">
          <label htmlFor="Q" className='lbl'>Q</label>
          <input type="number" name="Q" id="Q" onChange={(e)=>{q = e.target.value}}/>
          <button className="submit1" onClick={()=>{connectToServer()}}>Connect</button>
        </div>
        </div>

    </div>
  );
}

export default App;
