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

function main() {
    chooseLocalPath();
    clickButton(waitForObject(names.dialogBackupPushButton5QPushButton));
    clickButton(waitForObject(names.dialogSuccessPushButtonQPushButton));
}

