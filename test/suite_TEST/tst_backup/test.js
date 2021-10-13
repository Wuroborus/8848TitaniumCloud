import * as names from 'names.js';

function choosePath() {
    clickButton(waitForObject(names.dialogBackupPushButtonQPushButton));
    mouseClick(waitForObjectItem(names.splitterSidebarQSidebar, "c"), 56, 14, Qt.NoModifier, Qt.LeftButton);
    doubleClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Documents"), 65, 11, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObject(names.stackedWidgetTreeViewQTreeView), 70, 23, Qt.NoModifier, Qt.LeftButton);
    doubleClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "source"), 64, 15, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "little-source"), 60, 14, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
    clickButton(waitForObject(names.dialogBackupPushButton2QPushButton));
    mouseClick(waitForObjectItem(names.splitterSidebarQSidebar, "c"), 68, 20, Qt.NoModifier, Qt.LeftButton);
    doubleClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Music"), 42, 19, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
}

function compress() {
    clickButton(waitForObject(names.dialogBackupCheckBox2QCheckBox));
}

function pack() {
    clickButton(waitForObject(names.dialogBackupCheckBoxQCheckBox));
    type(waitForObject(names.dialogPacknameLineEditQLineEdit), "cdc");
    clickButton(waitForObject(names.dialogPacknamePushButtonQPushButton));
}

function pass() {
    clickButton(waitForObject(names.dialogBackupCheckBox3QCheckBox));
    mouseClick(waitForObject(names.dialogPasswordLineEditQLineEdit), 41, 6, Qt.NoModifier, Qt.LeftButton);
    type(waitForObject(names.dialogPasswordLineEditQLineEdit), "123456");
    mouseClick(waitForObject(names.dialogPasswordLineEdit2QLineEdit), 57, 17, Qt.NoModifier, Qt.LeftButton);
    type(waitForObject(names.dialogPasswordLineEdit2QLineEdit), "123456");
    clickButton(waitForObject(names.dialogPasswordPushButtonQPushButton));
}

function unpack() {
    clickButton(waitForObject(names.dialogBackupCheckBoxQCheckBox));
}

function unpass() {
    clickButton(waitForObject(names.dialogBackupCheckBox3QCheckBox));
}

function main() {
    clickButton(waitForObject(names.mainWindowPushButtonQPushButton));
    choosePath();
    for(i = 0; i < 10; i++) {
        clickButton(waitForObject(names.dialogBackupPushButton5QPushButton)); // backup
        clickButton(waitForObject(names.dialogSuccessPushButtonQPushButton)); // close success
    }
    pack();
    for(i = 0; i < 10; i++) {
        clickButton(waitForObject(names.dialogBackupPushButton5QPushButton)); // backup
        clickButton(waitForObject(names.dialogSuccessPushButtonQPushButton)); // close success
    }
    pass();
    for(i = 0; i < 10; i++) {
        clickButton(waitForObject(names.dialogBackupPushButton5QPushButton)); // backup
        clickButton(waitForObject(names.dialogSuccessPushButtonQPushButton)); // close success
    }
    compress();
    for(i = 0; i < 10; i++) {
        clickButton(waitForObject(names.dialogBackupPushButton5QPushButton)); // backup
        clickButton(waitForObject(names.dialogSuccessPushButtonQPushButton)); // close success
    }
    unpass();
    for(i = 0; i < 10; i++) {
        clickButton(waitForObject(names.dialogBackupPushButton5QPushButton)); // backup
        clickButton(waitForObject(names.dialogSuccessPushButtonQPushButton)); // close success
    }
    unpack();
    for(i = 0; i < 10; i++) {
        clickButton(waitForObject(names.dialogBackupPushButton5QPushButton)); // backup
        clickButton(waitForObject(names.dialogSuccessPushButtonQPushButton)); // close success
    }
}
