import { useRef, useState } from 'react'
import { Navigate, useLocation } from 'react-router-dom';
import './messanger.css'

export default function Messanger()
{ 
    const [usersKey,setKeys] = useState(new Map());
    const [msgArray,setMsg] = useState([]);
    let inputElement = useRef();
    const [username, setUsername] = useState("");
    const [othername, setOthername] = useState("");
    let d,n;

    let Crypto = require('../math');
    let crypt = new Crypto();

    const location = useLocation();
    const {data} = location?.state || {};

    if (data === {} || data === undefined)
    {
        Navigate({to:'/'})
    }
    else
    {
        if (username === "")
            setUsername(data.username);
    }

    // console.log(data.username);
    d=data.d;
    n=data.n;

    const ws = new WebSocket("ws://localhost:8082");

    ws.addEventListener("message",data=>{
        data = JSON.parse(data.data);
        if (data.type === "key")
        {
            if (data.username === null)
                return

            usersKey.set(data.username,[data.e,data.n]);
            setKeys(usersKey);
        }

        if (data.type === "msg")
        {
            if(data.username === username){
                let message = crypt.decrypt(data.msg,d,n);
                setMsg([...msgArray,{username:data.username2,msg:message}]);
            }
        }
    })

    const fetchPublicKey = (user)=>
    {
        ws.send(JSON.stringify({type:"getKey",username:user}));
    }

    const getPublicKey = (username)=>
    {
        if (usersKey.has(username) === false)
        {
            alert("Username not found,please try again");
            return [null,null];
        }
        return usersKey.get(username);
    }

    const encryptMessage = (msg,e,n2)=>
    {
        return crypt.encrypt(msg,parseInt(e),parseInt(n2));
    }

    const sendMsg = ()=>
    {
        let msg = inputElement.current.value;

        let [e,n2] = getPublicKey(othername);
        // console.log(othername+"=> e:"+e+" n:"+n);
        console.log("2:" , usersKey);
        if (e === null)
            return;

        msg = encryptMessage(msg,e,n2);

        ws.send(JSON.stringify({type:"msg",username1:username,username2:othername,msg:msg}));

        setMsg([...msgArray,{username:username,msg:inputElement.current.value}]);
        inputElement.current.value = "";

    }

    let messageInst = msgArray.map((value,index)=>{
        return(
        <div className='msgInstant' id={index} key={index}>
            <div className="messageContent">
                <h3 className='user' >{value.username}</h3>
                <p className='msgText'>{value.msg}</p>           
            </div>
        </div>
        )
    });

    return(
        <div className="mainContainer">

            <div className="inputContainer" style={{width:"35%"}}>
            <label htmlFor="Username" className='lbl'>Username</label>
            <input type="text" name="Username" id="Username"
            value={othername}
            onChange={(e)=>{
                fetchPublicKey(e.target.value);
                setOthername(e.target.value); 
            }}/>
            </div>

            <div className="MessageWindow">
                <div className="upperWindow">
                    {messageInst}
                </div>
                <div className="lowerWindow">
                    <input type="text" maxLength="50" id='Message'
                    ref={inputElement}
                    />
                    
                    <button className="submit" onClick={()=>{sendMsg()}}>
                        <svg xmlns="http://www.w3.org/2000/svg" height="1em" viewBox="0 0 448 512"><path d="M438.6 278.6c12.5-12.5 12.5-32.8 0-45.3l-160-160c-12.5-12.5-32.8-12.5-45.3 0s-12.5 32.8 0 45.3L338.8 224 32 224c-17.7 0-32 14.3-32 32s14.3 32 32 32l306.7 0L233.4 393.4c-12.5 12.5-12.5 32.8 0 45.3s32.8 12.5 45.3 0l160-160z"/></svg>
                    </button>
                </div>
            </div>
        </div>
    )
}