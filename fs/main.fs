let job n = async{
    do! Async.Sleep 1000
    return n*n
}

[job 2;job 3; job 4]
|>