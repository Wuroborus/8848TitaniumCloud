import * as names from 'names.js';

function main() {
    clickButton(waitForObject(names.mainWindowPushButtonQPushButton));
    clickButton(waitForObject(names.dialogBackupCheckBoxQCheckBox));
    type(waitForObject(names.dialogPacknameLineEditQLineEdit), "cdc");
    
}
