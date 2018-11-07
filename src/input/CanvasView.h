#ifndef _APE_VIEW_CANVASVIEW_H_
#define _APE_VIEW_CANVASVIEW_H_

#include <vector>
#include <map>
#include <functional>
#include <gtkmm.h>
#include <goocanvasmm.h>
#include <goocanvasmm/gridmodel.h>  // This is necessary for unknown reasons
#include "GraphicsParameters.h"
#include "Position.h"
#include "net/NetComponent.h"

class CanvasWindow;
class NetNode;
class Controller;

/**
 * The canvas manager in a CanvasWindow.
 */
class CanvasView {
public:
	/**
	 * Constructor
	 */
	explicit CanvasView(CanvasWindow *parent);

	/**
	 * Destructor
	 */
	~CanvasView();

	/**
	 * Set the controller object in the instance.
	 * Should be called directly after construction of the object.
	 */
	void putController(Controller *controller);

	/**
	 * Updates the changed item
	 */
	void itemChanged(std::shared_ptr<NetComponent> item);

	/**
	 * Unregisters item
	 */
	void itemRemoved(std::shared_ptr<NetComponent> item);

	/**
	 * Unregister all items
	 */
	void clearAllItems();

	/**
	 * Turn on or off snapping to the grid
	 */
	void setSnapToGrid(bool snap);

	/**
	 * Turn on or off highlighting enabled fransitions
	 */
	void setFireHighlight(bool highlight);

	/**
	 * Get the Goocanvas::Canvas from the view.
	 */
	Goocanvas::Canvas *getCanvas();

	/**
	 * Get the currently selected item, if a single one is selected.
	 * If nothing is selected or more than one item is selected, this function
	 * returns an empty std::shared_ptr.
	 */
	std::shared_ptr<NetComponent> getSelectedItem();

	/**
	 * Get the current multiple selection.
	 * If nothing is selected, the returned list is empty.
	 */
	std::vector<std::shared_ptr<NetComponent>> getMultipleSelection();

	/**
	 * Get the current scroll offset of the current canvas.
	 * The returned position is the point currently located in the centre of the
	 * canvas.
	 */
	Position getScrollOffset();

	/**
	 * Set the initial scrolloffset to store the initial scrolloffset the screen if
	 * setScrollOffset is called before the view is realized
	 */
	void setInitialScrollOffset(const Position &pos);

	/**
	 * Update the current scroll offset to the given position.
	 * The canvas is scrolled in such a way that the centre of the canvas
	 * corresponds to the given position.
	 */
	void setScrollOffset(Position posIn);


	// TODO: MAKE THIS PRIVATE?

	/// Unselect the current selection
	void unselectSelected();
	/// Register a new net item
	void registerNetItem(std::shared_ptr<NetComponent> item, bool doFireEnabledUpdate = true);
	/// Query the Controller for the current net and register that
	void registerBaseNet();
	/// Recompute bounds, e.g. on resize
	void updateCanvasBounds();
	/// Reset any current user state, like dragged objects and variables
	void resetActions();

	/// Execute code while the canvas is cleaned up for rendering
	void renderBracket(const std::function<void()> &body);
	void setViewportSize(size_t width, size_t height);
	void zoomIn();
	void zoomOut();
private:

	CanvasWindow *mParent;
	Controller *mController;
	Goocanvas::Canvas *mCanvas;
	Glib::RefPtr<Goocanvas::GroupModel> mRoot;

	double viewport_x = 0, viewport_y = 0, viewport_width = 0, viewport_height = 0;
	const double mZoomFactor = 2;
	double mZoom = 1.0;

	class ItemData {
	public:
		/**
		 * Constructs and calls update(), essentially.
		 * Only the main model is added to mItemModelMap of the parent
		 * class, and the link in mNetItemMap is created. Then, all
		 * stuff is added to mRoot.
		 */
		ItemData(CanvasView *parent, std::shared_ptr<NetComponent> netItem);

		/**
		 * Destructor
		 */
		~ItemData();

		/**
		 * Removes all stuff from mRoot and removes the main model from
		 * mItemModelMap and removes the net item from mNetItemMap.
		 */
		void deleteItemData();

		/**
		 * Change settings of and/or add/remove ItemModels in this
		 * thing according to any settings in the GraphicsParameters
		 * of the net item.
		 */
		void update();

		/**
		 * Set whether selected
		 */
		void setSelected(bool selected);

		/**
		 * Set whether transition is enabled
		 */
		void setEnabled(bool enabled);

		/**
		 * Get the NetComponent this ItemData corresponds to
		 */
		std::shared_ptr<NetComponent> getNetItem();

		/**
		 * Get the current main goo item model that this ItemData manages (may change)
		 */
		Glib::RefPtr<Goocanvas::ItemModelSimple> getCurrentMainModel();

		/**
		 * Returns true iff the given item was indeed a private item and should be
		 * forgotten about by the caller.
		 */
		bool registerPrivateItem(const Glib::RefPtr<Goocanvas::Item> &itemIn);

	private:
		/**
		 * The window this ItemData belongs to
		 */
		CanvasView *mParent;

		/**
		 * The net item that this thing refers to
		 */
		std::shared_ptr<NetComponent> mNetItem;

		/**
		 * Whether this item is selected
		 */
		bool mSelected = false;

		/**
		 * Whether this (presumably) transition is enabled
		 */
		bool mEnabled = false;

		/**
		 * The draw style (cached)
		 */
		GraphicsParameters::DrawStyle mCachedDrawStyle;

		/**
		 * Whether this item is curved (cached).
		 * This only applies for an arc
		 */
		bool mCachedCurved;

		/**
		 * The main item model, like the circle of a place
		 */
		Glib::RefPtr<Goocanvas::ItemModelSimple> mMain;

		// Extra item models that are needed for drawing
		Glib::RefPtr<Goocanvas::PolylineModel> mPolyUnderlay;  // for straight arrows
		Glib::RefPtr<Goocanvas::PathModel> mPathUnderlay;  // for curved arrows
		Glib::RefPtr<Goocanvas::PolylineModel> mArrowHead;  // for curved arrows
		Glib::RefPtr<Goocanvas::TextModel> mLabel;
		Glib::RefPtr<Goocanvas::TextModel> mTokenLabel;
		Glib::RefPtr<Goocanvas::TextModel> mCapacityLabel;
		std::vector<Glib::RefPtr<Goocanvas::EllipseModel>> mTokens;
		std::vector<Glib::RefPtr<Goocanvas::EllipseModel>> mControlDots;

		std::vector<Position> mTokenPositions;

		// HACK. This ptr will be added to the maps, so that the pointer is
		// actually SHARED.
		std::shared_ptr<ItemData> mThisPtr;

		bool mIsDraggingDot = false;
		double mDragMouseStartX, mDragMouseStartY;
		double mDragDotStartX, mDragDotStartY;

		void removeAllModels();

		void applySelectionAppearance();

		bool controlDotPressCallback(
				int indexIn, const Glib::RefPtr<Goocanvas::Item> &, GdkEventButton *);
		bool controlDotReleaseCallback(
				int indexIn, const Glib::RefPtr<Goocanvas::Item> &, GdkEventButton *);
		bool controlDotMotionCallback(
				int indexIn, const Glib::RefPtr<Goocanvas::Item> &, GdkEventMotion *);
	};

	std::map<Glib::RefPtr<Goocanvas::ItemModel>, std::shared_ptr<ItemData>> mItemModelMap;
	std::map<std::shared_ptr<NetComponent>, std::shared_ptr<ItemData>> mNetItemMap;

	Glib::RefPtr<Goocanvas::GridModel> mBackGrid;

	void createdCallback(
			const Glib::RefPtr<Goocanvas::Item> &item,
			const Glib::RefPtr<Goocanvas::ItemModel> &model);

	bool canvasEnterCallback(GdkEventCrossing *crossingEvent);
	bool canvasLeaveCallback(GdkEventCrossing *crossingEvent);

	void setModeCursor();

	bool groupButtonPressCallback(
			const Glib::RefPtr<Goocanvas::Item> &item,
			GdkEventButton *event);
	bool groupButtonReleaseCallback(
			const Glib::RefPtr<Goocanvas::Item> &item,
			GdkEventButton *event);
	bool groupButtonMotionCallback(
			const Glib::RefPtr<Goocanvas::Item> &item,
			GdkEventMotion *event);

	bool itemButtonPressCallback(
			const Glib::RefPtr<Goocanvas::Item> &item,
			GdkEventButton *event);
	bool itemButtonReleaseCallback(
			const Glib::RefPtr<Goocanvas::Item> &item,
			GdkEventButton *event);
	bool itemButtonMotionCallback(
			const Glib::RefPtr<Goocanvas::Item> &item,
			GdkEventMotion *event);

	void selectItem(std::shared_ptr<NetComponent> netItem);
	void multipleSelectAdd(std::shared_ptr<NetComponent> netItem);
	void multipleSelectRemove(std::shared_ptr<NetComponent> netItem);

	void updateFireEnabledMarkers();
	double mGridSize = 15;
	bool mDoSnapGrid = true;
	bool mDoFireHighlight = true;


	// SCROLLING
	bool mIsScrolling = false;
	bool mScrollConfirmed = false;
	double mScrollStartX, mScrollStartY;
	double mScrollOriginStartX, mScrollOriginStartY;
	double initScrollOffsetX, initScrollOffsetY;
	bool initialScroll = true;

	// DRAGGING
	bool mIsDragging = false;
	bool mDragConfirmed = false;  // whether mouse has moved away far enough already
	Glib::RefPtr<Goocanvas::Item> mDraggedGoo;
	Glib::RefPtr<Goocanvas::RectModel> mDragRect;
	std::shared_ptr<NetNode> mDraggedNetNode;
	double mDragStartX, mDragStartY;
	Position mDragStartPosition;


	// ARC DRAWING
	bool mIsDrawingArc = false;
	Glib::RefPtr<Goocanvas::PolylineModel> mDrawingArcPoly;  // poly mode
	Glib::RefPtr<Goocanvas::PathModel> mDrawingArcPath;  // path mode
	Glib::RefPtr<Goocanvas::PolylineModel> mDrawingArcArrowHead;  // path mode
	std::shared_ptr<NetNode> mDrawingArcStartNode;
	std::vector<Position> mDrawingArcPoints;

	// SELECTING
	std::shared_ptr<NetComponent> mSelectedItem = nullptr;
	std::vector<std::shared_ptr<NetComponent>> mMultipleSelection;

	/**
	 *	Calculates the real rectangle bounds, width and height based
	 *  upon the origin and end coordinates.
	 */
	void getRealRectBounds(const double &originX, const double &originY,
						   const double &endX, const double &endY,
						   double &width, double &height,
						   Position &topLeft, Position &topRight);

	/**
	 *	Return true when a position is within a rectangle bound.
	 */
	bool isWithinBounds(const Position &point,
						const Position &topLeft,
						const Position &bottomRight);

	void lowerAboveBack(const Glib::RefPtr<Goocanvas::ItemModel> &model);

	void updateDrawingArc();

	Position snapToGrid(Position pos);
	Position snapToGrid(double x, double y);

	static void adjustArrowEndpoint(
			const Glib::RefPtr<Goocanvas::PolylineModel> &poly,
			std::shared_ptr<NetNode> endNode);
	static void adjustArrowEndpoint(
			std::vector<Position> &positions, std::shared_ptr<NetNode> endNode);

	/**
	 * Generates curvy svg path data for a list of points.
	 * @return Pair of svg path string and back-tangent of last point.
	 */
	static std::pair<std::string, Vector2> generatePathData(const std::vector<Position> &p);
};

#endif
