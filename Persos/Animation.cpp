//
// Created by alex on 28/02/18.
//

#include "Animation.h"


Animation::Animation (Texture *textures, Vector2u imageCount, float switchTime) : _imageCount(imageCount),
                                                                                  _switchTime(switchTime),
                                                                                  _totalTime(0.0f)
{
    _currentImage.x = 0;
    _currentImage.y = 0;
    _textureRect.width = static_cast<int>(textures->getSize().x / float(_imageCount.x));
    _textureRect.height = static_cast<int>(textures->getSize().y / float(_imageCount.y));

}

/*Animation::Animation(Animation &animation):_imageCount(animation._imageCount), _switchTime(animation._switchTime), _totalTime(0.0f)
{
    _currentImage.x = 0;
    _currentImage.y = 0;
    _textureRect.width = static_cast<int>(_texture->getSize().x / float(_imageCount.x));
    _textureRect.height = static_cast<int>(_texture->getSize().y / float(_imageCount.y));
}*/

void Animation::Update (int row, float deltaTime)
{
    _currentImage.y = static_cast<unsigned int>(row);
    _totalTime += deltaTime;

    if (_totalTime >= _switchTime)
    {
        _totalTime -= _switchTime;
        _currentImage.x++;


        if (_currentImage.x >= _imageCount.x)
        {
            _currentImage.x = 0;
        }

        if (_currentImage.y >= _imageCount.y)
        {
            _currentImage.y = 0;
        }
    }

    _textureRect.left = _currentImage.x * _textureRect.width;
    _textureRect.top = _currentImage.y * _textureRect.height;

}


