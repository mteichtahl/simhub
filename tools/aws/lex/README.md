# setup instructions

1. Do a search/replace for awlarau-workshops- and replace with your-bucket-name in the region you are running this (us-east-1)
2. Do a search/replace for /Users/alarter/Larter/Security/credentials.json and replace with the location of a file that has this format:


{
  "accountId":123456789,
  "accessKeyId": "XXXXX",
  "secretAccessKey": "XXXXX",
  "region": "us-east-1"
}

Make sure you have the region set to the same region as step 1.

2a. run 
` npm install`


2b. In the lambda functions, run a grunt invoke to do a local test. Grunt push to push the deploy artefact to the S3 bucket. Grunt deploy will push on to the existing lambda function.

4. In common/config.json in the lambda folder, set the CFNStackPrefix to the name of the CFN stack you used to spin it up. That way, the local grunt deploy will work, otherwise, it can’t work out what lambda you mean.

Apart from that, everything should just spin up with the implementation you saw yesterday (with the permissions fixed – that was the problem). But – you must create the Slot manually, I didn’t automate it. It needs to be called KeyNames (or if you want to rename, update WhatsMyParameterIntent.json to match). I just manually created altitude, pitch, speed etc. If you ask ‘What’s my blah’ then the lambda handler will look in DDB for a record with title blah. If you say air speed, it will look for airspeed, so name accordingly.