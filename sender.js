const sleep = require('system-sleep');
const schedule = require('node-schedule');

function start_sender()
{
    console.log("Sender");
    let toSend = [1,1,1,1,1,1,1];
    let currentBitIndex = 0;
    const INTERVAL = 50;

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
                if(end - start > INTERVAL)
                {
                    console.log("Sending 1");
                    break;
                }
            }
        }
        else
        {
            sleep(INTERVAL);
        }

        currentBitIndex += 1;
    }
}


schedule.scheduleJob('0 * * * * *', start_sender);       
