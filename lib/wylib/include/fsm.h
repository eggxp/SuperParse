/** @defgroup FSM ����״̬��ʵ��(fsm.h)
 *  @author  ��߮
 *  @version 1.0
 *  @date    2004.11.16
 *  @{
 */
 //sdfasdfa
 //sadfsdafdsf

#ifndef fsmH
#define fsmH
#include <vcl.h>
#include "alist.h"
/**  �����¼�����ʱ��ִ�еĻص�����*/
typedef void  __fastcall (__closure *TFUN_EVENT_ACTION)();

/*! \class CTransitionEvent
    \brief ת���¼�������,�¼�ת���������ڶ���״̬��ת���¼�

    ����ΪCStat������
*/
class CTransitionEvent  
{
  private:
   int _EventID;             /**< �¼�ID,�����ظ� */
	 TFUN_EVENT_ACTION m_BeforeEventAction;    /**< �յ��¼�״̬ת��֮ ��ǰ�� ִ���Զ��庯�� */
	 TFUN_EVENT_ACTION m_AfterEventAction;     /**< �յ��¼�״̬ת��֮ ���� ִ���Զ��庯�� */

   int _DesStauID;   /**< �¼��������Ŀ��״̬ */
  public:
       /**
       * ���캯��
       * @param EventID       �¼�ID,�����ظ�
       * @param BeforeAction  �յ��¼�״̬ת��֮ ��ǰ�� ִ���Զ��庯��ָ��
       * @param AfterAction   �յ��¼�״̬ת��֮ ���� ִ���Զ��庯��ָ��
       * @param DesStauID     Ŀ��״̬ID,���¼���������ת����Ŀ��״̬
       * @see ~CTransitionEvent()
       * @return ��
       */
   __fastcall CTransitionEvent(int EventID,TFUN_EVENT_ACTION BeforeAction,TFUN_EVENT_ACTION AfterAction,int DesStauID){_EventID= EventID;m_BeforeEventAction=BeforeAction;m_AfterEventAction = AfterAction; _DesStauID = DesStauID;}
   /** ��������
   * �޲�������ֵ
   */
   __fastcall ~CTransitionEvent(){;}
       /**
       * ��ȡ�¼������ID
       * @see CTransitionEvent()
       * @return �¼������ID(int)
       */
   __inline   int GetEventID(){return _EventID;}
       /**
       * ִ��״̬ת��֮ "ǰ" ִ���¼�����
	   * @see DoAfterAction()
       * @return ת�����¼������ID(int)
	   */
   void  	  DoAfterAction();

	   /**
       * ִ��״̬ת��֮ "��" ִ���¼�����
       * @see DoBeforeAction()
       * @return ��
	   */
   int        DoBeforeAction();
};
//

/*! \class CStat
    \brief ״̬��ʾ��,���ڶ���״̬����״̬,�ʹ���״̬�л����¼�

    ����ΪCFSM_Manage������
*/
class CStat       
{
private:
  AList<CTransitionEvent> * TranstionList;  /**< ��״̬��ת���¼��б� */
  int        _ID;                          /**< ��״̬��ID */
  int        _ImageIndex;                  /**< ��״̬��ͼ�α�־���� */
  String     _Info;                       /**< ��״̬��˵�� */
  String     _Hint;                      /**< ��״̬����ϸ˵����Ϣ */
protected:
	       /**
       * ��ȡĳ�¼���������Index
       * @param EventID       �¼�ID
       * @see AddTransitionEvent()
       * @return ��Ӧ�¼�id������
       */
  int        GetTEIndex(int EventID); 
public:
       /**
       * ���캯��
       * @param StatID          ״̬ID,�����ظ�
       * @param StatImageIndex  ��״̬��ͼ������ID,����ͼ�λ���ʾ״̬
       * @param StatInfo        ��״̬����������
       * @param Hint            ��״̬����ϸ˵��
       * @see ~CStat()
       * @return ���캯��Ĭ��ֵ
       */
  __fastcall CStat(int StatID,int StatImageIndex,String StatInfo,String Hint);
  /** �������� */
  __fastcall ~CStat(); 
       /**
       * ����һ���¼��������
       * @param NewTE           ���û��������¼�����
       * @see AddTransitionEvent()
       * @return ��ӳɹ����� True,ʧ�ܷ��� False
       */
  bool __fastcall  AddTransitionEvent(CTransitionEvent *NewTE);     
         /**
       * ����һ���¼��������
       * @param EventID       �¼�ID,�����ظ�
       * @param BeforeEventAction  �յ��¼�״̬ת��֮ ��ǰ�� ִ���Զ��庯��ָ��
       * @param AfterAction   �յ��¼�״̬ת��֮ ���� ִ���Զ��庯��ָ��
       * @param DesStauID     Ŀ��״̬ID,���¼���������ת����Ŀ��״̬
       * @see AddTransitionEvent()
       * @return ��ӳɹ����� һ���µ�CTransitionEvent����ָ��(��CStat�����ͷ�,�û������ͷ�),ʧ�ܷ��� NULL
       */       
  CTransitionEvent *  __fastcall  AddTransitionEvent(int EventID,TFUN_EVENT_ACTION BeforeEventAction,TFUN_EVENT_ACTION AfterAction,int DesStauID);
        /**
       * ����¼������
       */
  __inline void __fastcall ClearTransitionEvent(){TranstionList->Clear();}  
         /**
       * ���ش�״̬���¼���������
       * @see AddTransitionEvent()
       * @return ����Ӱ���״̬���������¼���������
       */         
  __inline int __fastcall TECount(){return TranstionList->Count();}      
           /**
       * �������������¼�ִ��ת������,����ת�����Ŀ��״̬ID
       * @param EventID       �����¼�ID,��Ϊ����״̬ת����Դ��Ϣ
       * @see AddTransitionEvent()
       * @return ����ת�������״̬ID
       */    
  int __fastcall Transition(int EventID); 
           /**
       * ֪ͨ״̬ת���ɹ�,ִ��״̬��������
       * @see AddTransitionEvent()
       */    
  void __fastcall EventSuccess(int EventID);
             /**
       * ��ȡ״̬ID
       * @see GetImageIndex() 
       */    
  __inline int    GetID(){return _ID;}
       /**
       * ��ȡ״̬��ͼ���������
       * @see GetImageIndex() 
       */    
  __inline int    GetImageIndex(){return _ImageIndex;}
         /**
       * ��ȡ״̬��������Ϣ
       * @see GetImageIndex() GetInfo()
       */   
  __inline String GetInfo(){return _Info;}
         /**
       * ��ȡ״̬����ϸ˵����Ϣ
       * @see GetImageIndex() 
       */   
  __inline String GetHint(){return _Hint;}
};


/**�¼�ת��֪ͨ�ص�����ָ�붨��*/
typedef void  __fastcall (__closure *TFUN_EVENT_CHANAGE)(CStat *OldStat,CStat *NewStat);
class CFSM_Manage//����״̬����
{
private:
   AList<CStat> * StatList; //״̬�б�
   int _CurrentStatID; //��ǰ״̬ID
protected:
  int        GetStatIndex(int StatID);  //��ȡĳ�¼���������Index
  CStat *    GetStat(int StatID); //����ID��ȡ״̬����
public:
  __fastcall CFSM_Manage();
  __fastcall ~CFSM_Manage();
  __inline int __fastcall Count(){return StatList->Count();}  //����״̬������
 __inline void __fastcall ClearStat(){StatList->Clear();}  //���״̬��
 bool __fastcall  Add(CStat *NewStat); //����һ��״̬����
 CStat * Add(int StatID,int StatImageIndex,String StatInfo,String Hint);
 int __fastcall Transition(int EventID); //�������������¼�ִ��ת������,����ת�����Ŀ��״̬ID
 __inline int __fastcall GetCurrentStatID(){return _CurrentStatID;}
 void __fastcall SetStat(int NewStatID);//ǿ�����õ�ǰ��״̬ID
 __inline CStat *    GetCurrentStat(){return  GetStat(_CurrentStatID);} //��ȡ��ǰ״̬����ָ��
 TFUN_EVENT_CHANAGE  OnStausChanage;
 void       RefreshGUI();
};

//---------------------------------------------------------------------------
#endif


 /** @}*/ // ����״̬��