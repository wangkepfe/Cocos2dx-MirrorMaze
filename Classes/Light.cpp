#include"Light.h"

USING_NS_CC;

bool Light::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->scheduleUpdate();
	_changeHappen = true;
	return true;
}

void Light::update(float dt)
{
	if (_changeHappen)
	{
		removeAllChildren();
		_changeHappen = false;

		Size s = Director::getInstance()->getVisibleSize();

		int i, j, k, m, n;
		float x, y;

		recv_ok_num = 0;

		for (m = 0; m < receiver_num; m++)
		{
			i = receiver_pos[m].x;
			j = receiver_pos[m].y;
			map[i][j].state = Receiving;
		}

		opened_door_num = opened_door_index;
		for (n = 0; n < trigger_num; n++)
		{
			i = trigger_pos[n].x;
			j = trigger_pos[n].y;

			bool needReset = true;
			for (opened_door_index = 0; opened_door_index < opened_door_num; opened_door_index++)
			{
				if (opened_door_pos[opened_door_index] == Vec2(i, j))
				{
					needReset = false;
					break;
				}
			}

			if (needReset)
			{
				map[i][j].state = Receiving;
				switch (map[i][j].direc)
				{
				case down: map[i + 1][j].type = Door;
					break;
				case left: map[i][j + 1].type = Door;
					break;
				case up:   map[i - 1][j].type = Door;
					break;
				case right:map[i][j - 1].type = Door;
					break;
				default:
					break;
				}
			}
		}
		opened_door_index = 0;

		for (k = 0; k < emitter_num; k++)
		{
			i = emitter_pos[k].x;
			j = emitter_pos[k].y;
			x = (i + 0.5f) * GRID_SIZE;
			y = s.height - ((j + 0.5f) * GRID_SIZE);

			if (map[i][j].type == Emitter)
				calcuLightPath(Vec2(x, y) , map[i][j].direc, Color3B::WHITE, 1.0f);
			else if (map[i][j].type == Register)
			{
				Color3B regColor;
				switch (map[i][j].state)
				{
				case Red: regColor = Color3B::RED;
					break;
				case Yellow: regColor = Color3B::YELLOW;
					break;
				case Blue: regColor = Color3B::BLUE;
					break;
				case Orange: regColor = Color3B::ORANGE;
					break;
				case Purple: regColor = Color3B::MAGENTA;
					break;
				case Green: regColor = Color3B::GREEN;
					break;
				default: regColor = Color3B::WHITE;
					break;
				}
				calcuLightPath(Vec2(x, y), map[i][j].direc, regColor, 1.0f);
			}
		}
		
		if (recv_ok_num == receiver_num)
		{
			*p_win = 1;
		}
	}
}

void Light::handleBlock(BlockDirec direc, BlockInfo &info, Vec2 startpoint,Color3B color, float opacity, int i, int j)
{
	if (isGlass(info.type))
		mirrorReflection(startpoint, info.type, direc, info.direc, color, opacity);
	else if (isReceiver(info.type) && lightReceiver(info.type, direc, info.direc, color, info.state));
	else if (info.type == Register && lightRegister(direc, info.direc, color, info.state));
	else if (info.type == DoorTriger && doorTriggger(direc, info.direc, info.state, i, j));
}

void Light::calcuLightPath(cocos2d::Vec2 startPoint, BlockDirec direc, cocos2d::Color3B color, float opacity)
{
	if (opacity <= 0.05f)
		return;

	int i, j, k;
	float x, y;
	bool obstacle = 0;
	Size s = Director::getInstance()->getVisibleSize();

	j = startPoint.x / GRID_SIZE - 0.5f;
	k = (s.height - startPoint.y) / GRID_SIZE - 0.5f;

	opacity -= 0.05;

	switch (direc)
	{
	case up:
		for (i = 1; k - i >= 0; i++)
		{
			if (map[j][k - i].type != Nothing)
			{
				obstacle = 1;
				y = s.height - ((k - i + 0.5f) * GRID_SIZE);
				drawLight(startPoint, Vec2(startPoint.x, y), color, opacity);
				handleBlock(up, map[j][k - i], Vec2(startPoint.x, y), color, opacity, j, k - i);
				break;
			}
		}
		if(!obstacle)
			drawLight(startPoint, Vec2(startPoint.x, s.height), color, opacity);
		break;
	case down:
		for (i = 1; k + i < MAP_HEIGHT; i++)
		{
			if (map[j][k + i].type != Nothing)
			{
				obstacle = 1;
				y = s.height - ((k + i + 0.5f) * GRID_SIZE);
				drawLight(startPoint, Vec2(startPoint.x, y), color, opacity);
				handleBlock(down, map[j][k + i], Vec2(startPoint.x, y), color, opacity, j, k + i);
				break;
			}
		}
		if (!obstacle)
			drawLight(startPoint, Vec2(startPoint.x, 0), color, opacity);
		break;
	case left:
		for (i = 1; j - i >= 0; i++)
		{
			if (map[j - i][k].type != Nothing)
			{
				obstacle = 1;
				x = (j - i + 0.5f) * GRID_SIZE;
				drawLight(startPoint, Vec2(x, startPoint.y), color, opacity);
				handleBlock(left, map[j - i][k], Vec2(x, startPoint.y), color, opacity, j - i, k);
				break;
			}
		}
		if (!obstacle)
			drawLight(startPoint, Vec2(0, startPoint.y), color, opacity);
		break;
	case right:
		for (i = 1; j + i < MAP_LENGTH; i++)
		{
			if (map[j + i][k].type != Nothing)
			{
				obstacle = 1;
				x = (j + i + 0.5f) * GRID_SIZE;
				drawLight(startPoint, Vec2(x, startPoint.y), color, opacity);
				handleBlock(right, map[j + i][k], Vec2(x, startPoint.y), color, opacity, j + i, k);
				break;
			}
		}
		if (!obstacle)
			drawLight(startPoint, Vec2(s.width, startPoint.y), color, opacity);
		break;
	default:
		break;
	}
}

void Light::drawLight(cocos2d::Vec2 point1, cocos2d::Vec2 point2, cocos2d::Color3B color, float opacity)
{
	auto draw = DrawNode::create();
	draw->setLineWidth(5);
	draw->drawLine(point1, point2, Color4F(color.r/255.f, color.g/255.f, color.b/255.f, opacity));
	addChild(draw);
}

void Light::mirrorReflection(cocos2d::Vec2 point, BlockType glassType, BlockDirec lightDirec, BlockDirec blockDirec, cocos2d::Color3B color, float opacity)
{
	BlockDirec direc;

	if (coloredGlass(glassType, color) == false)
	{
		return;
	}

    if (glassType == TwoFaceMirror || glassType == Triangle)
	{
		if (lightDirec == up)
		{
			if (blockDirec == up || blockDirec == down)
				direc = left;
			else
				direc = right;
		}
		else if (lightDirec == down)
		{
			if (blockDirec == down || blockDirec == up)
				direc = right;
			else
				direc = left;
		}
		else if (lightDirec == left)
		{
			if (blockDirec == down || blockDirec == up)
				direc = up;
			else
				direc = down;
		}
		else if (lightDirec == right)
		{
			if (blockDirec == down || blockDirec == up)
				direc = down;
			else
				direc = up;
		}
		if (glassType == Triangle)
		{
			calcuLightPath(point, direc, color, opacity * 0.5f);
			calcuLightPath(point, lightDirec, color, opacity * 0.5f);
		}
		else if (glassType == TwoFaceMirror)
		{
			calcuLightPath(point, direc, color, opacity);
		}
	}
	else
	{
		bool reflect = false;
		if (lightDirec == up && blockDirec == up)
		{
			reflect = true;
			direc = left;
		}
		else if (lightDirec == up && blockDirec == left)
		{
			reflect = true;
			direc = right;
		}
		else if(lightDirec == down && blockDirec == down)
		{
			reflect = true;
			direc = right;
		}
		else if (lightDirec == down && blockDirec == right)
		{
			reflect = true;
			direc = left;
		}
		else if (lightDirec == left && blockDirec == down)
		{
			reflect = true;
			direc = up;
		}
		else if (lightDirec == left && blockDirec == left)
		{
			reflect = true;
			direc = down;
		}
		else if (lightDirec == right && blockDirec == up)
		{
			reflect = true;
			direc = down;
		}
		else if (lightDirec == right && blockDirec == right)
		{
			reflect = true;
			direc = up;
		}
		if (reflect)
			calcuLightPath(point, direc, color, opacity);
	}
}

bool Light::coloredGlass(BlockType glassType, cocos2d::Color3B &color)
{
	if (glassType == YellowGlass)
	{
		if (color == Color3B::WHITE)
			color = Color3B::YELLOW;
		else if (color == Color3B::RED)
			color = Color3B::ORANGE;
		else if (color == Color3B::BLUE)
			color = Color3B::GREEN;
		else if (color == Color3B::MAGENTA)
			return false;
	}
	else if (glassType == RedGlass)
	{
		if (color == Color3B::WHITE)
			color = Color3B::RED;
		else if (color == Color3B::YELLOW)
			color = Color3B::ORANGE;
		else if (color == Color3B::BLUE)
			color = Color3B::MAGENTA;
		else if (color == Color3B::GREEN)
			return false;
	}
	else if (glassType == BlueGlass)
	{
		if (color == Color3B::WHITE)
			color = Color3B::BLUE;
		else if (color == Color3B::YELLOW)
			color = Color3B::GREEN;
		else if (color == Color3B::RED)
			color = Color3B::MAGENTA;
		else if (color == Color3B::ORANGE)
			return false;
	}

	return true;
}

bool Light::lightRegister(BlockDirec lightDirec, BlockDirec blockDirec, cocos2d::Color3B color, BlockState &state)
{
	if (lightDirec == blockDirec)
	{
		BlockState colorState;
		if (color == Color3B::WHITE) colorState = White;
		else if (color == Color3B::BLUE) colorState = Blue;
		else if (color == Color3B::YELLOW) colorState = Yellow;
		else if (color == Color3B::RED) colorState = Red;
		else if (color == Color3B::GREEN) colorState = Green;
		else if (color == Color3B::MAGENTA) colorState = Purple;
		else if (color == Color3B::ORANGE) colorState = Orange;

		if (state != colorState)
		{
			state = colorState;
			_changeHappen = true;
			return true;
		}
	}
	return false;
}

bool Light::lightReceiver(BlockType type, BlockDirec lightDirec, BlockDirec blockDirec, cocos2d::Color3B color, BlockState &state)
{
	if (
			(
				(type == Receiver && color == Color3B::WHITE) ||
				(type == YellowReceiver && color == Color3B::YELLOW) ||
				(type == RedReceiver && color == Color3B::RED) ||
				(type == BlueReceiver && color == Color3B::BLUE) ||
				(type == OrangeReceiver && color == Color3B::ORANGE) ||
				(type == PurpleReceiver && color == Color3B::MAGENTA) ||
				(type == GreenReceiver && color == Color3B::GREEN)
			) &&			
			(
				(lightDirec == left && blockDirec == right) ||
				(lightDirec == right && blockDirec == left) ||
				(lightDirec == down && blockDirec == up) ||
				(lightDirec == up && blockDirec == down)
			)
		)
	{
		state = Received;
		recv_ok_num++;
		return true;
	}
	return false;
}

bool Light::doorTriggger(BlockDirec lightDirec, BlockDirec blockDirec, BlockState & state, int position_i, int position_j)
{
	if (		
		(lightDirec == left && blockDirec == right) ||
		(lightDirec == right && blockDirec == left) ||
		(lightDirec == down && blockDirec == up) ||
		(lightDirec == up && blockDirec == down)	
	   )
	{
		state = Received;
		_changeHappen = true;
		switch (blockDirec)
		{
		case down: map[position_i + 1][position_j].type = Nothing;
			break;
		case left: map[position_i][position_j + 1].type = Nothing;
			break;
		case up:   map[position_i - 1][position_j].type = Nothing;
			break;
		case right:map[position_i][position_j - 1].type = Nothing;
			break;
		default:
			break;
		}
		opened_door_pos[opened_door_index] = Vec2(position_i, position_j);
		opened_door_index++;
		return true;
	}
	return false;
}
 
void Light::setMap(BlockInfo ** _map)
{
	map = _map;
	int i, j, k = 0, m = 0, n = 0;
	Size s = Director::getInstance()->getVisibleSize();

	emitter_num = 0;
	receiver_num = 0;
	for (i = 0; i < MAX_EMITTER_NUMBER; i++)
	{
		emitter_pos[i] = Vec2::ZERO;
	}

	for (i = 0; i < MAP_LENGTH; i++)
	{
		for (j = 0; j < MAP_HEIGHT; j++)
		{
			if (map[i][j].type == Emitter || map[i][j].type == Register)
			{
				emitter_num++;
				emitter_pos[k++] = Vec2(i, j);
			}
			else if (isReceiver(map[i][j].type))
			{
				receiver_num++;
				receiver_pos[m++] = Vec2(i, j);
			}
			else if (map[i][j].type == DoorTriger)
			{
				trigger_num++;
				trigger_pos[n++] = Vec2(i, j);
			}
		}
	}
}