import * as names from 'names.js';

function main() {
    clickButton(waitForObject(names.mainWindowPushButton2QPushButton));
    clickButton(waitForObject(names.dialogRestorePushButtonQPushButton));
    mouseClick(waitForObjectItem(names.splitterSidebarQSidebar, "c"), 57, 19, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Pictures"), 66, 14, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
    clickButton(waitForObject(names.dialogRestorePushButton2QPushButton));
    mouseClick(waitForObjectItem(names.splitterSidebarQSidebar, "c"), 53, 18, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.splitterSidebarQSidebar, "c"), 81, 14, Qt.NoModifier, Qt.LeftButton);
    doubleClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Music"), 55, 15, Qt.NoModifier, Qt.LeftButton);
    doubleClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "back\\_up\\_0"), 82, 16, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "source"), 299, 15, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
    clickButton(waitForObject(names.dialogRestorePushButton5QPushButton));
}
