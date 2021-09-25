import * as names from 'names.js';

function main() {
    clickButton(waitForObject(names.mainWindowPushButton3QPushButton));
    clickButton(waitForObject(names.dialogComparePushButton3QPushButton));
    mouseClick(waitForObjectItem(names.splitterSidebarQSidebar, "c"), 32, 20, Qt.NoModifier, Qt.LeftButton);
    doubleClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Music"), 46, 15, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "back\\_up\\_1"), 55, 12, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
    clickButton(waitForObject(names.dialogComparePushButton4QPushButton));
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "back\\_up\\_3"), 70, 14, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
    clickButton(waitForObject(names.dialogComparePushButtonQPushButton));
}
