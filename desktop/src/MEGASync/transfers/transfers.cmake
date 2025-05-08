
set(DESKTOP_APP_TRANSFERS_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/model/InfoDialogTransfersProxyModel.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/DuplicatedNodeDialog.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/DuplicatedNodeInfo.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/DuplicatedNodeItem.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/DuplicatedUploadChecker.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/InfoDialogTransferLoadingItem.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferWidgetColumnsManager.h
    ${CMAKE_CURRENT_LIST_DIR}/model/TransfersManagerSortFilterProxyModel.h
    ${CMAKE_CURRENT_LIST_DIR}/model/TransfersSortFilterProxyBaseModel.h
    ${CMAKE_CURRENT_LIST_DIR}/model/TransfersModel.h
    ${CMAKE_CURRENT_LIST_DIR}/model/TransferMetaData.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/SomeIssuesOccurredMessage.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/InfoDialogTransferDelegateWidget.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/InfoDialogTransfersWidget.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/MegaTransferDelegate.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/MegaTransferView.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/MediaTypeFilterWidget.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferBaseDelegateWidget.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferItem.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferManager.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferManagerDelegateWidget.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferManagerLoadingItem.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransfersStatusWidget.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransfersSummaryWidget.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferScanCancelUi.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferWidgetHeaderItem.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransfersWidget.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransfersAccountInfoWidget.h
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferManagerStatusHeaderWidget.h
)

set(DESKTOP_APP_TRANSFERS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/model/TransfersModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/DuplicatedNodeDialog.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/DuplicatedNodeInfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/DuplicatedNodeItem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/DuplicatedUploadChecker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/InfoDialogTransferLoadingItem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferWidgetColumnsManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/model/InfoDialogTransfersProxyModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/model/TransfersManagerSortFilterProxyModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/SomeIssuesOccurredMessage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/model/TransferMetaData.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/InfoDialogTransferDelegateWidget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/InfoDialogTransfersWidget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/MegaTransferDelegate.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/MegaTransferView.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/MediaTypeFilterWidget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferBaseDelegateWidget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferItem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferManagerDelegateWidget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferManagerLoadingItem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransfersStatusWidget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransfersSummaryWidget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferScanCancelUi.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferWidgetHeaderItem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransfersWidget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransfersAccountInfoWidget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui/TransferManagerStatusHeaderWidget.cpp
)


target_sources_conditional(${ExecutableTarget}
   FLAG WIN32
   QT_AWARE
   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/gui/win/TransferWidgetHeaderItem.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/win/TransferManagerDelegateWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/win/TransferManager.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/win/TransfersWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/win/TransferManagerLoadingItem.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/win/TransferManagerDragBackDrop.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/win/InfoDialogTransfersWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/win/InfoDialogTransferDelegateWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/win/InfoDialogTransferLoadingItem.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/win/TransfersStatusWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/win/TransfersSummaryWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/win/SomeIssuesOccurredMessage.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/win/TransfersAccountInfoWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/win/MediaTypeFilterWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/win/DuplicatedNodeDialog.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/win/DuplicatedNodeItem.ui
)

target_sources_conditional(${ExecutableTarget}
   FLAG APPLE
   QT_AWARE
   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/gui/macx/TransferWidgetHeaderItem.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/macx/TransferManagerDelegateWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/macx/TransferManager.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/macx/TransfersWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/macx/TransferManagerLoadingItem.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/macx/TransferManagerDragBackDrop.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/macx/InfoDialogTransfersWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/macx/InfoDialogTransferDelegateWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/macx/InfoDialogTransferLoadingItem.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/macx/TransfersStatusWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/macx/TransfersSummaryWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/macx/SomeIssuesOccurredMessage.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/macx/TransfersAccountInfoWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/macx/MediaTypeFilterWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/macx/DuplicatedNodeDialog.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/macx/DuplicatedNodeItem.ui
)

target_sources_conditional(${ExecutableTarget}
   FLAG UNIX AND NOT APPLE
   QT_AWARE
   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/gui/linux/TransferWidgetHeaderItem.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/linux/TransferManagerDelegateWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/linux/TransferManager.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/linux/TransfersWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/linux/TransferManagerLoadingItem.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/linux/TransferManagerDragBackDrop.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/linux/InfoDialogTransfersWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/linux/InfoDialogTransferDelegateWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/linux/InfoDialogTransferLoadingItem.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/linux/TransfersStatusWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/linux/TransfersSummaryWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/linux/SomeIssuesOccurredMessage.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/linux/TransfersAccountInfoWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/linux/MediaTypeFilterWidget.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/linux/DuplicatedNodeDialog.ui
   ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/linux/DuplicatedNodeItem.ui
)

if (WIN32)
    set_property(TARGET ${ExecutableTarget}
        APPEND PROPERTY AUTOUIC_SEARCH_PATHS
        ${CMAKE_CURRENT_LIST_DIR}/gui/win
        ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/win
        ${CMAKE_CURRENT_LIST_DIR}/gui/ui
    )
elseif (APPLE)
    set_property(TARGET ${ExecutableTarget}
        APPEND PROPERTY AUTOUIC_SEARCH_PATHS
        ${CMAKE_CURRENT_LIST_DIR}/gui/macx
        ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/macx
        ${CMAKE_CURRENT_LIST_DIR}/gui/ui
    )
else()
    set_property(TARGET ${ExecutableTarget}
        APPEND PROPERTY AUTOUIC_SEARCH_PATHS
        ${CMAKE_CURRENT_LIST_DIR}/gui/linux
        ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs/linux
        ${CMAKE_CURRENT_LIST_DIR}/gui/ui
    )
endif()

set (DESKTOP_APP_TRANSFERS_UI_FILES
    ${CMAKE_CURRENT_LIST_DIR}/gui/ui/TransferManagerStatusHeaderWidget.ui
)

target_sources(${ExecutableTarget}
    PRIVATE
    ${DESKTOP_APP_TRANSFERS_HEADERS}
    ${DESKTOP_APP_TRANSFERS_SOURCES}
    ${DESKTOP_APP_TRANSFERS_UI_FILES}
)

set (INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/model
    ${CMAKE_CURRENT_LIST_DIR}/gui
    ${CMAKE_CURRENT_LIST_DIR}/gui/ui
    ${CMAKE_CURRENT_LIST_DIR}/gui/DuplicatedNodeDialogs
)

target_include_directories(${ExecutableTarget} PRIVATE ${INCLUDE_DIRECTORIES})

