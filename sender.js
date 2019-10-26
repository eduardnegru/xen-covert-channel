function start_sender()
{
    console.log("Sender");
    while(true)
    {
        let start = new Date().getTime();

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
}

(async () => {

    let timer = setInterval(()=> {
        
        let date = new Date();
        let seconds = date.getSeconds();
        let miliseconds = date.getMilliseconds();
        if (seconds === 0 && miliseconds === 0)
        {
            clearInterval(timer);
            start_sender();
        }
    }, 1);
})();