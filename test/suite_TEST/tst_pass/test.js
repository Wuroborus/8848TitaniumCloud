import * as names from 'names.js';

function main() {
    mouseClick(waitForObject(names.mainWindowCentralWidgetQWidget), 361, 187, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.mainWindowPushButtonQPushButton));
    clickButton(waitForObject(names.dialogBackupPushButtonQPushButton));
    mouseClick(waitForObjectItem(names.splitterSidebarQSidebar, "c"), 53, 14, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Music"), 126, 2, Qt.NoModifier, Qt.LeftButton);
    type(waitForObject(names.stackedWidgetTreeViewQTreeView), "c");
    type(waitForObject(names.stackedWidgetTreeViewQTreeView), "d");
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
    clickButton(waitForObject(names.dialogBackupPushButtonQPushButton));
    mouseClick(waitForObjectItem(names.splitterSidebarQSidebar, "c"), 67, 15, Qt.NoModifier, Qt.LeftButton);
    doubleClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Documents"), 81, 8, Qt.NoModifier, Qt.LeftButton);
    doubleClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "source"), 106, 22, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "little-source"), 207, 17, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
    mouseDrag(waitForObject(names.dialogBackupDialogBackup), 138, 172, -6, -3, 1, Qt.LeftButton);
    clickButton(waitForObject(names.dialogBackupPushButton2QPushButton));
    mouseClick(waitForObjectItem(names.splitterSidebarQSidebar, "c"), 60, 6, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Music"), 85, 13, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
    clickButton(waitForObject(names.dialogBackupPushButton5QPushButton));
    
}
