import * as names from 'names.js';

function main() {
    clickButton(waitForObject(names.mainWindowPushButton3QPushButton));
    clickButton(waitForObject(names.dialogComparePushButton3QPushButton));
    doubleClick(waitForObjectItem(names.splitterSidebarQSidebar, "c"), 38, 20, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Documents"), 62, 12, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Documents"), 64, 13, Qt.NoModifier, Qt.LeftButton);
    doubleClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Documents"), 68, 14, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "back\\_up\\_9"), 93, 20, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
    clickButton(waitForObject(names.dialogComparePushButton4QPushButton));
    sendEvent("QWheelEvent", waitForObject(names.stackedWidgetTreeViewQTreeView), 65, 192, -120, 0, 2);
    sendEvent("QWheelEvent", waitForObject(names.stackedWidgetTreeViewQTreeView), 65, 192, -120, 0, 2);
    sendEvent("QWheelEvent", waitForObject(names.stackedWidgetTreeViewQTreeView), 65, 192, -120, 0, 2);
    sendEvent("QWheelEvent", waitForObject(names.stackedWidgetTreeViewQTreeView), 65, 192, -120, 0, 2);
    sendEvent("QWheelEvent", waitForObject(names.stackedWidgetTreeViewQTreeView), 65, 192, -120, 0, 2);
    doubleClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "back\\_up\\_11"), 84, 13, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
    clickButton(waitForObject(names.dialogComparePushButtonQPushButton));
}
