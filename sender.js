const sleep = require('system-sleep');

function start_sender()
{
    console.log("Sender");
    let toSend = [1,0,1,1,1,0,0];
    let currentBitIndex = 0;
    
    while(true)
    {
        let start = new Date().getTime();
        let bit = toSend[currentBitIndex];
        
        if(currentBitIndex === toSend.length)
        {
            break;
        }
        
        if(bit === 1)
        {
            while(true)
            {
                let end = new Date().getTime();
                if(end - start > 25)
                {
                    console.log("Sending 1");
                    break;
                }
            }
        }
        else
        {
            sleep(25);
        }

        currentBitIndex += 1;
    }
}

(async () => {
    
    while(true)
    {
        let date = new Date();
        let seconds = date.getSeconds();
        let miliseconds = date.getMilliseconds();
     
        if(seconds === 0 && miliseconds ===0)
        {
            start_sender();
            break;
        }
    }       
})();