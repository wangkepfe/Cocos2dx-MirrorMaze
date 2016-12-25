#include"DefineAndEnum.h"

bool isGlass(BlockType type)
{
	if (type == OneFaceMirror ||
		type == YellowGlass ||
		type == RedGlass ||
		type == BlueGlass ||
		type == TwoFaceMirror ||
		type == Triangle ||
		type == FixedMirror)
		return true;
	return false;
}

bool isReceiver(BlockType type)
{
	if (type == Receiver ||
		type == YellowReceiver ||
		type == RedReceiver ||
		type == BlueReceiver ||
		type == PurpleReceiver ||
		type == GreenReceiver ||
		type == OrangeReceiver)
		return true;
	return false;
}

const std::string getFileNameByType(BlockType type, BlockState state)
{	
	std::string fileName("image/");

	switch (type)
	{
	case Emitter: fileName += "LightEmitter";
		break;
	case Receiver: fileName += "LightAbsorber";
		break;
	case OneFaceMirror: fileName += "oneFaceMirror";
		break;
	case TwoFaceMirror: fileName += "twoFaceMirror";
		break;
	case Triangle: fileName += "triangle";
		break;
	case FixedMirror: fileName += "fixed";
		break;
	case DoorTriger: fileName += "doorTrigger";
		break;
	case Door: fileName += "door";
		break;
	case Register: fileName += "register";
		break;
	case YellowGlass: fileName += "yellow11";
		break;
	case RedGlass: fileName += "red12";
		break;
	case BlueGlass: fileName += "blue13";
		break;
	case YellowReceiver: fileName += "YellowAbsorber21";
		break;
	case RedReceiver: fileName += "RedAbsorber22";
		break;
	case BlueReceiver: fileName += "BlueAbsorber23";
		break;
	case OrangeReceiver: fileName += "OrangeAbsorber24";
		break;
	case PurpleReceiver: fileName += "PurpleAbsorber25";
		break;
	case GreenReceiver: fileName += "GreenAbsorber26";
		break;
	default: fileName += "ui2";
		break;
	}

	switch (state)
	{
	case Nostate:
		break;
	case Receiving:
		break;
	case Received: fileName += "_2";
		break;
	case White:
		break;
	case Red: fileName += "Red";
		break;
	case Yellow: fileName += "Yellow";
		break;
	case Blue: fileName += "Blue";
		break;
	case Orange: fileName += "Orange";
		break;
	case Purple: fileName += "Purple";
		break;
	case Green: fileName += "Green";
		break;
	default:
		break;
	}
	fileName += ".png";

	return fileName;
}

bool isTutoringLevel(int level)
{
	return false;
}
