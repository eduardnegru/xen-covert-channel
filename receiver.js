const schedule = require('node-schedule');

function start_receiver()
{
    console.log("Receiver");
    const INTERVAL = 50;

    while(true)
    {
        let i = 0;    
        let start = new Date().getTime();

        while(true)
        {
            let end = new Date().getTime();
            i += 1;
            if(end - start > INTERVAL)
            {
                console.log("Received ", i);
                break;
            }    
        }
    }
}

schedule.scheduleJob('0 * * * * *', start_receiver);       

// (async () => {

//     while(true)
//     {
//         let date = new Date();
//         let seconds = date.getSeconds();
//         let miliseconds = date.getMilliseconds();
     
//         if(seconds === 0 && miliseconds ===0)
//         {
//             start_receiver();
//             break;
//         }
//     }
// })();