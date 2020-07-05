
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if(CheckAttribute(npchar, "quest.questflag"))
			{
				dialog.text = SelectDeliveryCitizenDialog(npchar);
				link.l1 = "�����, �� ������������.";
				link.l1.go = "delivery_passenger_mission_accept";
				link.l2 = "�� �����, ��� ���� ��� ����������.";
				link.l2.go = "delivery_passenger_mission_decline";
			}
			else
			{
				dialog.text = "��� ��� �� ���� ����?";
				link.l1 = "������, � ��� �����.";
				link.l1.go = "exit";
			}
			
			NextDiag.TempNode = "First time";
		break;

		case "delivery_passenger_mission_accept":
			dialog.text = "������� ��� �������������.";
			link.l1 = "�� �� ���.";
			link.l1.go = "pass_accept_exit";
		break;

		case "delivery_passenger_mission_decline":
			dialog.text = "��� ��, ��� ���� �����.";
			link.l1 = "�� ��������.";
			link.l1.go = "pass_decline_exit";
		break;

		case "drink_man":
			dialog.text = "� ��� ���� ������ �������. ���� ��� �������. �! � ��� ���? ��������? ��.. ���.. ���� �������? �����, ������ ��������? ��. ������ 1 �������� �� ��, ������ �� ������, ��... ���.. ��... �������... ��� ���.. ��.. ��������! �! ��.. ��������!";
			link.l1 = "�������?!";
			link.l1.go = "drink_man_1";
			link.l2 = "�� ���� � ��� �� ������.";
			link.l2.go = "drink_man_1_3";
		break;

		case "drink_man_1":
			dialog.text = "���� � �� ������!! �� ��� �����.. ���� ���.. �! ���.. �������� �����! ���� �������! ��... ������ �� �������� ����! � ������� ������!";
			link.l1 = "�����?!";
			link.l1.go = "drink_man_1_1";
		break;

		case "drink_man_1_1":
			dialog.text = "� ���? �����?! ���.. ������� ����� ����, �������� ���� 1 ��������. ��!";
			link.l1 = "� ���� � ���� ��������� �����������. �����, �� �������� ���� ��� ������� ����-������ � ������?";
			link.l1.go = "drink_man_1_2";
		break;

		case "drink_man_1_2":
			dialog.text = "����! ���� ����������! ��������� �� ���� �� ���������� ��� ������ ������� �����?!";
			link.l1 = "��� ��������.";
			link.l1.go = "exit";
			AddDialogExitQuest("drink_man_leave");
		break;

		case "drink_man_1_3":
			dialog.text = "��������? ��� ������ � ���� ���� � �������?! � ��� ����� �� ���������? �! � ������! ��� ������������ ������������! ����� ����� ����������! ��!";
			link.l1 = "������ ��� �� ���� ������ �� ��������!";
			link.l1.go = "drink_man_1_4";
		break;

		case "drink_man_1_4":
			dialog.text = "����?!! ���� �� ������� �� ����� ���� �� ����������������?! � ��� ���� ������ ���������!";
			link.l1 = "��, �������? �������, ������� ������ ��� ����� �� �������� ������ ���� �������� ������.";
			link.l1.go = "drink_man_1_5";
			link.l2 = "��������? ��� ��. ������� � ������ �� �� �����, ����� � ������ �� �������� � ��� ���������. �� � ���� ���� �������� �������� �� �������.";
			link.l2.go = "drink_man_1_6";
		break;

		case "drink_man_1_5":
			dialog.text = "���?! ������� � ������ �������� ������ ���������!";
			link.l1 = "�����. � �������, � �� �� ������ ����.";
			link.l1.go = "exit";
			AddDialogExitQuest("drink_man_leave");
		break;

		case "drink_man_1_6":
			dialog.text = "������! ��! ������� ����� � �������� ������� ��������! � ����� ������ ���� ��� ��������!";
			link.l1 = "�������. � �� �� ������ ���� ����� �����.";
			link.l1.go = "exit"; 
			AddDialogExitQuest("drink_man_duel");
		break;

		case "pass_accept_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AcceptDeliveryPassengerQuest(npchar);
		break;

		case "pass_decline_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeletePassengerQuest(npchar);
		break;

		case "FencingTutorial":
			NextDiag.TempNode = "FencingTutorial";
			dialog.text = "�����������, �������! � ����, �� ��������� - �� ������ �� ������ �������� �� ��������� ����������?";
			link.l1 = "�������, � ������������� ��������.";
			link.l1.go = "FencingTutorial1";
			link.l2 = "���������, ���. ��� � ��� ����.";
			link.l2.go = "exit";
		break;

		case "FencingTutorial1":
			dialog.text = "� ��� ��� �������� ������ ���� ������: ������� ����, ������� ������� ��������� �����������, �� ������ ������ ������� ����� �������; ������� ����, ��������� ������ �����������, �� � ���������� ������ �������, ��� �������;\n����������� ����, ������� �������� � ��� ����� �������, �� �������� ������� ���� ���������� � ������� ������� �����������; � �������, �������� ����, ���������� ����� ������� � ��������� ����������� ���� ����������� � ���������������� �������� �� ���.\n����� ��� �������� ��� ���� ������: ����, ������� ������������ ��������� ������ �� ����������� ����� ����� ����; �����������, � ������� �������� ����� ������� � ������� ���� ���������� � �������� ������� ����������� ��� ����������; � ����, �������� ������� ����� � ������ ��������� �����, �� ������� ������� ���������� ������������ � ����������� ����.";
			link.l1 = "������� �� �����.";
			link.l1.go = "tutorial_exit";
		break;

		case "ShipSailingTutorial":
			NextDiag.TempNode = "ShipSailingTutorial";
			dialog.text = "�������, � ���� ���������� ��� ������� � ���, ��� ��������� ��������. ��� ����� ���������� ��� � ������� ���������.";
			link.l1 = "�������, � ������������� ��������.";
			link.l1.go = "ShipSailingTutorial1";
			link.l2 = "���������, ���. ��� � ��� ����.";
			link.l2.go = "exit";
		break;

		case "ShipSailingTutorial1":
			dialog.text = "���������� ��������� ������ ����� ��������, � �� �������������� ����������� �����������. ��������, �������, ���������� ������� ����������� ����� �������, ����� ������� ������ ����� ��� ��, ������� �������� � �������� ������� ��������, �� ���� ��������� ������� ������� �� �����.\n� ��� ������� ���������, ��� �� ���������� �������� ������� ����� ������� ��������, �� ����� �����������, � ������� - ��������� ������ ����� �� �������� ����������� �� ���������� ����. ������������ ���������� ������� ��������� ����� � ������ ������� �� ���, ��� �������� ��������� ����� - ��� ������� ��� ��������� � ��� ������ �������.\n��� ����, ����� ����� ��������� ������� �� �������, ����� �������� ���� ������� � ����� ���, ����� ��� ���� ��� ���������� �� ����������� ����������� ����� ����������, � �������� �� ������ ����������. ��� ������ ����� �� ������� � ������ '�������', ��� ����� �������� ����� ��� �����������.";
			link.l1 = "������� �� �����.";
			link.l1.go = "tutorial_exit";
		break;

		case "HireCrewTutorial":
			NextDiag.TempNode = "HireCrewTutorial";
			dialog.text = "������� - ������ ������ �������, � �������� ������� �����, ��� � ��� �������� ������ �����. � ���� ���������� ���, ��� � ��� �������� �������.";
			link.l1 = "�������, � ������������� ��������.";
			link.l1.go = "HireCrewTutorial1";
			link.l2 = "���������, ���. ��� � ��� ����.";
			link.l2.go = "exit";
		break;

		case "HireCrewTutorial1":
			dialog.text = "������ ����, �������� �������� �� �������, ��������� � ������� � �������� ������������� �����������. ��������� � ������������, �� ������ ������� ���� ����� �������. � ���� ���� ������������ ���������� ������������� ������ ������� ������� ���� (�������, ��������, ������� � ���������), ������� �� ������ ������, � ���� �����.\n����� ������������ ������ � ���� ����� ������� � �����, ������� ����� ������. ���� ���� ������� �������� � ����� �����, �� ���� ������� �������� � ������� ������� �������� ��� ���������� �� ����� �����.\n���� �� �������� ������ ������ � �����-���� �������� ����������, ������� �� ���� ������ ������� ����, ����� ������� ����������� ���������.";
			link.l1 = "������� �� �����.";
			link.l1.go = "tutorial_exit";
		break;

		case "OfficersTutorial":
			NextDiag.TempNode = "OfficersTutorial";
			dialog.text = "�� ������� ������ �������� � ���, ��� �������� ��������, �������?";
			link.l1 = "�������, � ������������� ��������.";
			link.l1.go = "OfficersTutorial1";
			link.l2 = "���������, ���. ��� � ��� ����.";
			link.l2.go = "exit";
		break;

		case "OfficersTutorial1":
			dialog.text = "������� ������ �������� � �������, ����� ����� ����������. ��������� � ������������, �� ������ ������� ���� ����� ��������. � ���� ������ ������� � ������� ����� ������ �� ���� �������� - ������ � ������� ���� ����������� �����. �������������� � �������� ����� ����� ��, ��� � ������ ��������� - ��� �������� ���� � ������ � ����� ��� ��, ��� � ��.\n��� ��������������, ������ � ����� ����� � ����������� ���������� ����� ������������ � ����. � ��������� ������ ������� ������� ����� - � ������� ������� ���� �������� � ��������, � ���� ���� �������� ����� �� �������������, ��� ���������� ����� ������, � � ����� ������ �� ������� ���.\n���� �� �������� ������ ������ � �����-���� �������� ����������, ������� �� ���� ������ ������� ����, ����� ������� ����������� ���������.";
			link.l1 = "������� �� �����.";
			link.l1.go = "tutorial_exit";
		break;

		case "ShipUpgradeTutorial":
			NextDiag.TempNode = "ShipUpgradeTutorial";
			dialog.text = "���� ������, �������, � ���� ���������� ��� � ���, ��� ��������������� ��� �������.";
			link.l1 = "�������, � ������������� ��������.";
			link.l1.go = "ShipUpgradeTutorial1";
			link.l2 = "���������, ���. ��� � ��� ����.";
			link.l2.go = "exit";
		break;

		case "ShipUpgradeTutorial1":
			dialog.text = "��������������� ������� ����� �� �����. ��������� ������������ ��������� ��� �������� ������, ������, � ����� ���, �������� � ���������� ����� ������ �������.\n��� ������� � ������� �������� ��� ������ ���������, ������ �� ������� ����� ���� ������������ � ����������. ��������� ����� ����� ���� ���� ���������� - ����. ����� �� ����� ��� - ���������� ����� � ���������. ��������� �������� ������ �����, �� ������� ������� ����������� � ������ ��������������.\n���� �� �������� ������ ������ � �����-���� �������� ����������, ������� �� ���� ������ ������� ����, ����� ������� ����������� ���������.";
			link.l1 = "������� �� �����.";
			link.l1.go = "tutorial_exit";
		break;

		case "TradeOperationsTutorial":
			NextDiag.TempNode = "TradeOperationsTutorial";
			dialog.text = "���� �� ������ ������� ������� ��������� ��������, � ���� ���� ��� ���� �������, �������.";
			link.l1 = "�������, � ������������� ��������.";
			link.l1.go = "TradeOperationsTutorial1";
			link.l2 = "���������, ���. ��� � ��� ����.";
			link.l2.go = "exit";
		break;

		case "TradeOperationsTutorial1":
			dialog.text = "�������� �� �������� ����� �������, ��� ��������� - ���� ������� ���������� ������, ������� ����� � ������, � ����� ��������� �������� �������� � ������, ����� �� ������� ������ ������� � ������ ����� ��, ��� ����� ����� �����.\n�� ������ ������� ���� �������, � ������� �� ������ ��������� � �������� ������. ����� ������ � ������ ������� �������� ��, ������� ������� �����������, � ������� - ��, ������� ������� ������������. ��������������, ���� �� ����� ����� ���� � ��� �������, ������� ��� ���������� � ������������, � ���� - � ���, ������� ��� �����������.\n���� �� �������� ������ ������ � �����-���� �������� ����������, ������� �� ���� ������ ������� ����, ����� ������� ����������� ���������.";
			link.l1 = "������� �� �����.";
			link.l1.go = "tutorial_exit";
		break;

		case "DeliveryTradeTutorial":
			NextDiag.TempNode = "DeliveryTradeTutorial";
			dialog.text = "��� ���������, �������? �� ������ �� ������ �������� � �������� ������?";
			link.l1 = "�������, � ������������� ��������.";
			link.l1.go = "DeliveryTradeTutorial1";
			link.l2 = "���������, ���. ��� � ��� ����.";
			link.l2.go = "exit";
		break;

		case "DeliveryTradeTutorial1":
			dialog.text = "������� �� �������� ������ ������� �� ��� ����: �������� ����� �� �������, �� ������� �� �������� �������, � ������, � �������� - �������� ������ � ������ ������� � ��, ��� ��� ���� �������. ���� ��� ����� ������� ����� �� ������ �������, �� ���� ������� ���� �������� ��� ��� ��������� �������, � ����������, ������� ������ ����� - ����� � �������� ��� �������.\n���� �� ��� ����� �������� ����� � ������ �������, �� ��������� ��� �����, ����� ��, ��������� � �������� �������� � ������, � ���������� � ����� ������ - ��� �������, ������� ��� ��� �������. �� ������, ���� �� � ���������� ����������� ������� ��������� ����� ������, ��� �������� �������� ������ ���������� �� ���� ������, ���� �� ������ ������� ��������� �������.\n��� ������� ��������, ������� ����� ���� ��� �������, ������ ����� ��������������� ����, � ��� ������� ��������, � ������� ����� ���������� ��� ����������� ������ ��� ��������� ������� - ��������������.";
			link.l1 = "������� �� �����.";
			link.l1.go = "tutorial_exit";
		break;

		case "DeliveryItemTutorial":
			NextDiag.TempNode = "DeliveryItemTutorial";
			dialog.text = "�� ������ �� ������ �������� � ���������� ��������, �������? ��������� �� ����� ����������, �� � �� ����� �������.";
			link.l1 = "�������, � ������������� ��������.";
			link.l1.go = "DeliveryItemTutorial1";
			link.l2 = "���������, ���. ��� � ��� ����.";
			link.l2.go = "exit";
		break;

		case "DeliveryItemTutorial1":
			dialog.text = "������ ����, ������� ���� ��� ���������� �������, �����, ����� �� ��� ��������� ����-������ ������������ �������, ��� ������� ���-������ ���� ������� � �������� ��� �����. ����, ������� ����� ������ �������, ����� ��� � ��, � ������� ��� �������, ������ ���� ��� � �������. ������� ������� ��� ������� �������, ��� ����� ��������� � ���������� �� ��������.\n��� ������� ��������, ������� ����� ���� ��� �������, ������ ����� ��������������� ����, � ��� ������� ��������, � ������� ����� ���������� ��� ����������� ������ ��� ��������� ������� - ��������������.";
			link.l1 = "������� �� �����.";
			link.l1.go = "tutorial_exit";
		break;

		case "DeliveryPassengerTutorial":
			NextDiag.TempNode = "DeliveryPassengerTutorial";
			dialog.text = "�������, � ���� ���-��� ���������� � ��������� ����������, ���� ��� ���������.";
			link.l1 = "�������, � ������������� ��������.";
			link.l1.go = "DeliveryPassengerTutorial1";
			link.l2 = "���������, ���. ��� � ��� ����.";
			link.l2.go = "exit";
		break;

		case "DeliveryPassengerTutorial1":
			dialog.text = "��������, �������� ����� ����-�� �������, �������� ����� �� ��������� ������, � ����������� ������ �������� ������� ��� �������� ����-������ ������ ������ - ��� ������ ���� ����������� � ��� �� ����, ���� �� ����������� �� ��������. ������ ��� ����� ��������� ������� ��������� �� ������ ������� � ������� ��� ����, ��� �� �������� �������. ����� ��������� ������ ���� ��� � �������.\n�������� ��������� � ����� ����������, �� ������ ������������ �� �������� - ���� ��������� �� ��������� �� �����, �������� ��� � ����� �������� � ���������� � ���, ����� �������� ���� �����; ���� �� ������� ��� ��� ����������, �� �� ��� � ��������.\n��� ������� ��������, ������� ����� ���� ��� �������, ������ ����� ��������������� ����, � ��� ������� ��������, � ������� ����� ���������� ��� ����������� ������ ��� ��������� ������� - ��������������.";
			link.l1 = "������� �� �����.";
			link.l1.go = "tutorial_exit";
		break;

		case "ShipEscortTutorial":
			NextDiag.TempNode = "ShipEscortTutorial";
			dialog.text = "������������, �������! ���� ������, � �������� ��� � ���, ��� ������������ �������.";
			link.l1 = "�������, � ������������� ��������.";
			link.l1.go = "ShipEscortTutorial1";
			link.l2 = "���������, ���. ��� � ��� ����.";
			link.l2.go = "exit";
		break;

		case "ShipEscortTutorial1":
			dialog.text = "������ ������� �� ������������� ������� ������ ���� ����� - ������ ������� �� �������, ��� ��� ���� �������, � ������, � �������� - ������������� ������� �� ������ ������� � ��, ��� �� �������� �������. ����� ������� �� ������ �������� � ������� ��� � �����������.\n���� ������� ����� ����������� �� ������ �������, �� �� ������������� � ��� ���, ����� �� ������� � ����. ���� �� ��� ����� ��������� �� ������ �������, ��, ������ ����, ��� ���� ������� ����� � ������� � ���������� � ��� ���������.\n��������� ������ ����������, ��� ����� ����� � ������� � ���������� � ��������� ��������������� �����, ����� ��������� �������. �������� ������� �� ������� ����������� ������� ����� � ����, ��� ��� ��� ���.\n��� ������� ��������, ������� ����� ���� ��� �������, ������ ����� ��������������� ����, � ��� ������� ��������, � ������� ����� ���������� ��� ����������� ������ ��� ��������� ������� - ��������������.";
			link.l1 = "������� �� �����.";
			link.l1.go = "tutorial_exit";
		break;

		case "SinkShipTutorial":
			NextDiag.TempNode = "SinkShipTutorial";
			dialog.text = "�� ������� ������ �������� � �������� �� ���������� �������? � ������� � ���� ����������, � ��� �� ���������� ��� ����� ���������.";
			link.l1 = "�������, � ������������� ��������.";
			link.l1.go = "SinkShipTutorial1";
			link.l2 = "���������, ���. ��� � ��� ����.";
			link.l2.go = "exit";
		break;

		case "SinkShipTutorial1":
			dialog.text = "�������� � ������� ��� - ��������� ����, �������� ���� � ����� ������ ����� � ������, ��� � ���. ������� ����� �������, ������� � �������, ����� � ������� � ��������� ��� ������ �����. ���� �� ������ �������, ��, ����� � ���� ����� � ��������, �� ������� ������� ����������. �������� ��� � ������������� � ��������, ������� ��� ��� �������, �� ��������.\n��� ������� ��������, ������� ����� ���� ��� �������, ������ ����� ��������������� ����, � ��� ������� ��������, � ������� ����� ���������� ��� ����������� ������ ��� ��������� ������� - ��������������.";
			link.l1 = "������� �� �����.";
			link.l1.go = "tutorial_exit";
		break;

		case "CaptureShipTutorial":
			NextDiag.TempNode = "CaptureShipTutorial";
			dialog.text = "���� ������, � ���� ���������� ��� � �������� �� ������ ��������, �������. ��� ��������� ����, � ����� ������ ����� ������ ����� ��� � ����� �������.";
			link.l1 = "�������, � ������������� ��������.";
			link.l1.go = "CaptureShipTutorial1";
			link.l2 = "���������, ���. ��� � ��� ����.";
			link.l2.go = "exit";
		break;

		case "CaptureShipTutorial1":
			dialog.text = "������ ��� ������� �� ����� �������, ��� ����� ������ ������������ � ���������� �������. ���� ���������� ������ � ����������, ������������� � ���� �������, ����� � ������� � ��������� ��� ������ ������ ��� �����.\n���� �� ������ �������, ��, ����� � ���� ����� � ��������, �� ������� ���� ������� ����������.�������� ��� �� �������, � ������� ��� �������, ������� ��� ������� ��������, ����� ������������� ������� �� ���� ������ �������, ����� ���� �� ������ ������������ � ������ ���������� �� ��������.\n��� ������� ��������, ������� ����� ���� ��� �������, ������ ����� ��������������� ����, � ��� ������� ��������, � ������� ����� ���������� ��� ����������� ������ ��� ��������� ������� - ��������������.";
			link.l1 = "������� �� �����.";
			link.l1.go = "tutorial_exit";
		break;

		case "SlavesTutorial":
			NextDiag.TempNode = "SlavesTutorial";
			dialog.text = "�������, �� ������� �� ������ ������� � ������������? ������ ������� �� ��� ������� �������, �� ������ �������� �������� ��������� ����� �������.";
			link.l1 = "�������, � ������������� ��������.";
			link.l1.go = "SlavesTutorial1";
			link.l2 = "���������, ���. ��� � ��� ����.";
			link.l2.go = "exit";
		break;

		case "SlavesTutorial1":
			dialog.text = "������� �� �������� ������������� ���������� ����� ����� �������� � �������������, ������� ����� ��������� �� ������ �������. ����� ����� ������, ���������� ������� � ��������� ���������� � ����� ��������. �������� ������ ���������� �����, �� ������ ����� �� �� ������� ������������, ������� ��� ��� �������.\n��� ������� ��������, ������� ����� ���� ��� �������, ������ ����� ��������������� ����, � ��� ������� ��������, � ������� ����� ���������� ��� ����������� ������ ��� ��������� ������� - ��������������.";
			link.l1 = "������� �� �����.";
			link.l1.go = "tutorial_exit";
		break;

		case "tutorial_exit":
			NextDiag.CurrentNode = "First Time";
			DialogExit();
			CompleteTutorial(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}