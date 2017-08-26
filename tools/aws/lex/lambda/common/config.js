
function Config()
{
  var config = {initialised:false};

  try
  {
    //console.log("Initialising from configuration file...");
    if ( process.env['LAMBDA_TASK_ROOT'] == null )
    {
      config = JSON.parse(require('fs').readFileSync('./common/config.json', 'utf8'));
    }
    else
    {
      config = JSON.parse(require('fs').readFileSync('common/config.json', 'utf8'));
    }

    return config;
  }
  catch (ex)
  {
      console.log("Could not load configuration -> " + ex.message);
  }

}

module.exports = new Config();
