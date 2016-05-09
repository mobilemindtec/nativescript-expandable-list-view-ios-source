//
//  NSExpandableTableView.h
//  
//

#import <UIKit/UIKit.h>

@class NSExpandableTableView;

typedef enum {
    UIExpansionStyleCollapsed = 0,
    UIExpansionStyleExpanded = 1,
    UIExpansionHeaderStyleCollapsed = 2,
    UIExpansionHeaderStyleExpanded = 3    
} UIExpansionStyle;


@protocol UIExpandingTableViewCell <NSObject>

@property (nonatomic, assign, getter = isLoading) BOOL loading;

@property (nonatomic, readonly) UIExpansionStyle expansionStyle;
- (void)setExpansionStyle:(UIExpansionStyle)style animated:(BOOL)animated;

@end



@protocol NSExpandableTableViewDatasource <UITableViewDataSource>

@required
- (BOOL)tableView:(NSExpandableTableView *)tableView canExpandSection:(NSInteger)section;
- (BOOL)tableView:(NSExpandableTableView *)tableView needsToDownloadDataForExpandableSection:(NSInteger)section;
- (UITableViewCell<UIExpandingTableViewCell> *)tableView:(NSExpandableTableView *)tableView expandingCellForSection:(NSInteger)section;

@end



@protocol NSExpandableTableViewDelegate <UITableViewDelegate>

@required
- (void)tableView:(NSExpandableTableView *)tableView downloadDataForExpandableSection:(NSInteger)section;

@optional
- (void)tableView:(NSExpandableTableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPathWhileAnimatingSection:(NSIndexPath *)indexPath;

- (void)tableView:(NSExpandableTableView *)tableView willExpandSection:(NSUInteger)section animated:(BOOL)animated;
- (void)tableView:(NSExpandableTableView *)tableView didExpandSection:(NSUInteger)section animated:(BOOL)animated;

- (void)tableView:(NSExpandableTableView *)tableView willCollapseSection:(NSUInteger)section animated:(BOOL)animated;
- (void)tableView:(NSExpandableTableView *)tableView didCollapseSection:(NSUInteger)section animated:(BOOL)animated;

@end



@interface NSExpandableTableView : UITableView <UITableViewDelegate, UITableViewDataSource> {
@private
    id<UITableViewDelegate, NSExpandableTableViewDelegate> __weak _myDelegate;
    id<UITableViewDataSource, NSExpandableTableViewDatasource> __weak _myDataSource;
    
    NSMutableDictionary *_expandableSectionsDictionary;     // will store BOOLs for each section that is expandable
    NSMutableDictionary *_showingSectionsDictionary;        // will store BOOLs for the sections state (nil: not expanded, 1: expanded)
    NSMutableDictionary *_downloadingSectionsDictionary;    // will store BOOLs for the sections state (nil: not downloading, YES: downloading)
    NSMutableDictionary *_animatingSectionsDictionary;
    
    NSInteger _maximumRowCountToStillUseAnimationWhileExpanding;
    
    BOOL _onlyDisplayHeaderAndFooterViewIfTableViewIsNotEmpty;
    UIView *_storedTableHeaderView;
    UIView *_storedTableFooterView;
}

@property (nonatomic, weak) id<NSExpandableTableViewDelegate> delegate;

// discussion
// you wont receive any callbacks for row 0 in an expandable section anymore
@property (nonatomic, weak) id<NSExpandableTableViewDatasource> dataSource;

// discussion
// never use tableView.delegate/ tableView.dataSource as a getter. setDataSource will set _myDataSource, etc. so use these getters instead
@property (nonatomic, readonly, weak) id<NSExpandableTableViewDelegate> myDelegate;
@property (nonatomic, readonly, weak) id<NSExpandableTableViewDatasource> myDataSource;

@property (nonatomic, assign) NSInteger maximumRowCountToStillUseAnimationWhileExpanding;

@property (nonatomic, assign) BOOL onlyDisplayHeaderAndFooterViewIfTableViewIsNotEmpty;

@property (nonatomic, assign) UITableViewRowAnimation reloadAnimation;

// call tableView:needsToDownloadDataForExpandableSection: to make sure we can expand the section, otherwise through exception
- (void)expandSection:(NSInteger)section animated:(BOOL)animated;
- (void)collapseSection:(NSInteger)section animated:(BOOL)animated;
- (void)cancelDownloadInSection:(NSInteger)section;
- (void)reloadDataAndResetExpansionStates:(BOOL)resetFlag;

- (BOOL)canExpandSection:(NSUInteger)section;
- (BOOL)isSectionExpanded:(NSInteger)section;

@end

@interface NSExpandableTableViewControllerHeaderCell : UITableViewCell <UIExpandingTableViewCell>{
    UIImageView *thumbsViewArrowUp;
    UIImageView *thumbsViewArrowDown;
}


@property (nonatomic, assign, getter = isLoading) BOOL loading;

@property (nonatomic, readonly) UIExpansionStyle expansionStyle;
- (void)setExpansionStyle:(UIExpansionStyle)expansionStyle animated:(BOOL)animated;

@end

