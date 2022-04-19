#include "dialogs.h"
#include "types.h"

void wxj::showErrorDialog(std::string msg)
{
    wxMessageBox(msg, "Error", wxICON_ERROR);
}
