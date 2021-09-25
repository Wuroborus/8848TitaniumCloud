import * as names from 'names.js';

function chooseLocalPath()
{
    clickButton(waitForObject(names.mainWindowPushButtonQPushButton));
    clickButton(waitForObject(names.dialogBackupPushButtonQPushButton));
    mouseClick(waitForObjectItem(names.splitterSidebarQSidebar, "c"), 43, 14, Qt.NoModifier, Qt.LeftButton);
    doubleClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Documents"), 51, 15, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "source"), 56, 19, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
    clickButton(waitForObject(names.dialogBackupPushButton2QPushButton));
    mouseClick(waitForObjectItem(names.splitterSidebarQSidebar, "c"), 36, 14, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Music"), 62, 17, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
}

function compress()
{
    mouseClick(waitForObject(names.dialogBackupDialogBackup), 285, 319, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.dialogBackupCheckBox2QCheckBox));
}

function pack()
{
    clickButton(waitForObject(names.dialogBackupCheckBoxQCheckBox));
    type(waitForObject(names.dialogPacknameLineEditQLineEdit), "chenyukun");
    clickButton(waitForObject(names.dialogPacknamePushButtonQPushButton));
}

function pass()
{
    clickButton(waitForObject(names.dialogBackupCheckBox3QCheckBox));
    mouseClick(waitForObject(names.dialogPasswordLineEditQLineEdit), 63, 19, Qt.NoModifier, Qt.LeftButton);
    type(waitForObject(names.dialogPasswordLineEditQLineEdit), "<NumPad1>");
    type(waitForObject(names.dialogPasswordLineEditQLineEdit), "<NumPad2>");
    type(waitForObject(names.dialogPasswordLineEditQLineEdit), "<NumPad3>");
    type(waitForObject(names.dialogPasswordLineEditQLineEdit), "<NumPad4>");
    type(waitForObject(names.dialogPasswordLineEditQLineEdit), "<NumPad5>");
    mouseClick(waitForObject(names.dialogPasswordLineEdit2QLineEdit), 91, 27, Qt.NoModifier, Qt.LeftButton);
    type(waitForObject(names.dialogPasswordLineEdit2QLineEdit), "<NumPad1>");
    type(waitForObject(names.dialogPasswordLineEdit2QLineEdit), "<NumPad2>");
    type(waitForObject(names.dialogPasswordLineEdit2QLineEdit), "<NumPad3>");
    type(waitForObject(names.dialogPasswordLineEdit2QLineEdit), "<NumPad4>");
    type(waitForObject(names.dialogPasswordLineEdit2QLineEdit), "<NumPad5>");
    clickButton(waitForObject(names.dialogPasswordPushButtonQPushButton));
}

function main() {
    chooseLocalPath();
    
    compress(); 
    //pack();
    //pass();
    
    clickButton(waitForObject(names.dialogBackupPushButton5QPushButton));
}

