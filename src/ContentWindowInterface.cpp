#include "ContentWindowInterface.h"
#include "ContentWindow.h"
#include "main.h"

ContentWindowInterface::ContentWindowInterface(boost::shared_ptr<ContentWindow> contentWindow)
{
    contentWindow_ = contentWindow;

    // copy all members from contentWindow
    if(contentWindow != NULL)
    {
        contentWidth_ = contentWindow->contentWidth_;
        contentHeight_ = contentWindow->contentHeight_;
        x_ = contentWindow->x_;
        y_ = contentWindow->y_;
        w_ = contentWindow->w_;
        h_ = contentWindow->h_;
        centerX_ = contentWindow->centerX_;
        centerY_ = contentWindow->centerY_;
        zoom_ = contentWindow->zoom_;
        selected_ = contentWindow->selected_;
    }
}

boost::shared_ptr<ContentWindow> ContentWindowInterface::getContentWindow()
{
    return contentWindow_.lock();
}

void ContentWindowInterface::getContentDimensions(int &contentWidth, int &contentHeight)
{
    contentWidth = contentWidth_;
    contentHeight = contentHeight_;
}

void ContentWindowInterface::getCoordinates(double &x, double &y, double &w, double &h)
{
    x = x_;
    y = y_;
    w = w_;
    h = h_;
}

void ContentWindowInterface::getPosition(double &x, double &y)
{
    x = x_;
    y = y_;
}

void ContentWindowInterface::getSize(double &w, double &h)
{
    w = w_;
    h = h_;
}

void ContentWindowInterface::getCenter(double &centerX, double &centerY)
{
    centerX = centerX_;
    centerY = centerY_;
}

double ContentWindowInterface::getZoom()
{
    return zoom_;
}

bool ContentWindowInterface::getSelected()
{
    return selected_;
}

void ContentWindowInterface::fixAspectRatio(ContentWindowInterface * source)
{
    if(g_mainWindow->getConstrainAspectRatio() != true || (contentWidth_ == 0 && contentHeight_ == 0))
    {
        return;
    }

    double aspect = (double)contentWidth_ / (double)contentHeight_;
    double screenAspect = (double)g_configuration->getTotalWidth() / (double)g_configuration->getTotalHeight();

    aspect /= screenAspect;

    double w = w_;
    double h = h_;

    if(aspect > w_ / h_)
    {
        h = w_ / aspect;
    }
    else if(aspect <= w_ / h_)
    {
        w = h_ * aspect;
    }

    // we don't want to call setSize unless necessary, since it will emit a signal
    if(w != w_ || h != h_)
    {
        w_ = w;
        h_ = h;

        if(source == NULL || dynamic_cast<ContentWindow *>(this) != NULL)
        {
            if(source == NULL)
            {
                source = this;
            }

            setSize(w_, h_);
        }
    }
}

void ContentWindowInterface::setContentDimensions(int contentWidth, int contentHeight, ContentWindowInterface * source)
{
    if(source == this)
    {
        return;
    }

    contentWidth_ = contentWidth;
    contentHeight_ = contentHeight;

    fixAspectRatio(this);

    if(source == NULL || dynamic_cast<ContentWindow *>(this) != NULL)
    {
        if(source == NULL)
        {
            source = this;
        }

        emit(contentDimensionsChanged(contentWidth_, contentHeight_, source));
    }
}

void ContentWindowInterface::setCoordinates(double x, double y, double w, double h, ContentWindowInterface * source)
{
    if(source == this)
    {
        return;
    }

    x_ = x;
    y_ = y;
    w_ = w;
    h_ = h;

    fixAspectRatio(this);

    if(source == NULL || dynamic_cast<ContentWindow *>(this) != NULL)
    {
        if(source == NULL)
        {
            source = this;
        }

        emit(coordinatesChanged(x_, y_, w_, h_, source));
    }
}

void ContentWindowInterface::setPosition(double x, double y, ContentWindowInterface * source)
{
    if(source == this)
    {
        return;
    }

    x_ = x;
    y_ = y;

    if(source == NULL || dynamic_cast<ContentWindow *>(this) != NULL)
    {
        if(source == NULL)
        {
            source = this;
        }

        emit(positionChanged(x_, y_, source));
    }
}

void ContentWindowInterface::setSize(double w, double h, ContentWindowInterface * source)
{
    if(source == this)
    {
        return;
    }

    w_ = w;
    h_ = h;

    fixAspectRatio(this);

    if(source == NULL || dynamic_cast<ContentWindow *>(this) != NULL)
    {
        if(source == NULL)
        {
            source = this;
        }

        emit(sizeChanged(w_, h_, source));
    }
}

void ContentWindowInterface::setCenter(double centerX, double centerY, ContentWindowInterface * source)
{
    if(source == this)
    {
        return;
    }

    centerX_ = centerX;
    centerY_ = centerY;

    if(source == NULL || dynamic_cast<ContentWindow *>(this) != NULL)
    {
        if(source == NULL)
        {
            source = this;
        }

        emit(centerChanged(centerX_, centerY_, source));
    }
}

void ContentWindowInterface::setZoom(double zoom, ContentWindowInterface * source)
{
    if(source == this)
    {
        return;
    }

    zoom_ = zoom;

    if(source == NULL || dynamic_cast<ContentWindow *>(this) != NULL)
    {
        if(source == NULL)
        {
            source = this;
        }

        emit(zoomChanged(zoom_, source));
    }
}

void ContentWindowInterface::setSelected(bool selected, ContentWindowInterface * source)
{
    if(source == this)
    {
        return;
    }

    selected_ = selected;

    if(source == NULL || dynamic_cast<ContentWindow *>(this) != NULL)
    {
        if(source == NULL)
        {
            source = this;
        }

        emit(selectedChanged(selected_, source));
    }
}

void ContentWindowInterface::moveToFront(ContentWindowInterface * source)
{
    if(source == this)
    {
        return;
    }

    if(source == NULL || dynamic_cast<ContentWindow *>(this) != NULL)
    {
        if(source == NULL)
        {
            source = this;
        }

        emit(movedToFront(source));
    }
}

void ContentWindowInterface::destroy(ContentWindowInterface * source)
{
    if(source == this)
    {
        return;
    }

    if(source == NULL || dynamic_cast<ContentWindow *>(this) != NULL)
    {
        if(source == NULL)
        {
            source = this;
        }

        emit(destroyed(source));
    }
}