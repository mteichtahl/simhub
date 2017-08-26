////////////////////////////////////
//
// Enums
//
////////////////////////////////////
function Enums()
{
  this.ErrorTypes =
  {
    ///////////////////////////////////////////////////////////////
    //
    // Error Consts
    //
    ///////////////////////////////////////////////////////////////
    ERR_OK                                : 0,
    ERR_UNKNOWN                           : 1,
    ERR_EXCEPTION                         : 2,
    ERR_UNAUTHORISED                      : 3,
    ERR_RESOURCE_TIMEOUT                  : 4,

  }
}

module.exports = new Enums();
