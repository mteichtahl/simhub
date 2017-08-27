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

    ERR_KEYNAME_LOOKUP_FAILED             : 100,
    ERR_UNEXPECTED_KEYNAME_COUNT          : 101,

  }

}

module.exports = new Enums();
