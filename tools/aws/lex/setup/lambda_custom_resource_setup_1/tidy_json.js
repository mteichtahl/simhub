
var json =
{ RequestType: 'Create',
ServiceToken: 'arn:aws:lambda:us-east-1:111111111111:function:aidemo-CustomResourceSetupEnvironmentPhase1',
ResponseURL: 'https://cloudformation-custom-resource-response-useast1.s3.amazonaws.com/arn%3Aaws%3Acloudformation%3Aus-east-1%3A111111111111%3Astack/aidemo/7cca4fd0-fb14-11e6-a442-50d5ca6e60e6%7CSetupEnvironmentPhase1%7C624a8e53-5f36-431e-b327-fecee00813a4?AWSAccessKeyId=AKIAJNXHFR7P7YGKLDPQ&Expires=1488004837&Signature=MBOpaZSfHOzeqsHrdVECI7Ooo6A%3D',
StackId: 'arn:aws:cloudformation:us-east-1:111111111111:stack/aidemo/7cca4fd0-fb14-11e6-a442-50d5ca6e60e6',
RequestId: '624a8e53-5f36-431e-b327-fecee00813a4',
LogicalResourceId: 'SetupEnvironmentPhase1',
ResourceType: 'Custom::SetupEnvironmentPhase1',
ResourceProperties:
{ ServiceToken: 'arn:aws:lambda:us-east-1:111111111111:function:aidemo-CustomResourceSetupEnvironmentPhase1',
RESTAPIId: '9z0aiojx13',
AWSAccountId: '111111111111',
Region: 'us-east-1',
StackName: 'aidemo' } }


console.log(JSON.stringify(json));
