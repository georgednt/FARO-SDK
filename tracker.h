/* Generated code.  Do not modify. */

#ifndef __TRACKER_H__
#define __TRACKER_H__

#ifdef _UNICODE
#ifndef UNICODE
#define UNICODE
#endif
#endif

#ifdef _EXPORTING
#define CLASS_DECLSPEC    _declspec(dllexport)
#else
#define CLASS_DECLSPEC    _declspec(dllimport)
#define JNICALL
#endif

void CLASS_DECLSPEC trackerDeleteString( LPTSTR ptr);
bool CLASS_DECLSPEC trackerSetInstallDir( TCHAR	*dir );
bool CLASS_DECLSPEC trackerSetAndCheckInstallDir( TCHAR	*dir );

class CLASS_DECLSPEC SMXException
{
private:
    TCHAR    msg[200];

public:
    SMXException( TCHAR    exceptionMsg[] );
    virtual ~SMXException();

    virtual void getMsg( TCHAR    exceptionMsg[],
                 int     maxLen           );
};

class CLASS_DECLSPEC TrkDrvException : public SMXException
{
private:
    TCHAR    msg[200];

public:
    TrkDrvException( TCHAR    exceptionMsg[] );
    virtual ~TrkDrvException();

    void getMsg( TCHAR    exceptionMsg[],
                 int     maxLen           );
};

class CLASS_DECLSPEC BaseDriverObject
{
public:
    BaseDriverObject();

    virtual ~BaseDriverObject();

};

class CLASS_DECLSPEC DriverStringPointer : public BaseDriverObject
{
public:
    DriverStringPointer(LPTSTR stringDataArg);

    virtual ~DriverStringPointer();

    LPTSTR getStringData();
private:
    LPTSTR	stringData;
};

class CLASS_DECLSPEC SMXObjectArray
{
private:
    BaseDriverObject** elementBuffer;
    int   elementCount;

public:
    SMXObjectArray( int  numElements );

    virtual ~SMXObjectArray();

    virtual int getNumElements();

    virtual void setElement(int index, BaseDriverObject* element);

    virtual LPVOID getElement(int index);
};

class CLASS_DECLSPEC TrkDrvObjectArray : public SMXObjectArray
{
private:
    BaseDriverObject** elementBuffer;
    int   elementCount;

public:
    TrkDrvObjectArray( int  numElements );

    virtual ~TrkDrvObjectArray();

    int getNumElements();

    void setElement(int index, BaseDriverObject* element);

    LPVOID getElement(int index);
};

//***********************************************
class CLASS_DECLSPEC TrackerException
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    TrackerException(  );

    TrackerException( LPTSTR param0 );

    explicit TrackerException( LPVOID param0 );

    virtual ~TrackerException();

    LPTSTR getText(  );

    int getCode(  );

    static TrackerException * createInstance( LPVOID envVoid, LPVOID objVoid );

public:
};

//***********************************************
class CLASS_DECLSPEC AbortedException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    AbortedException(  );

    explicit AbortedException( LPVOID param0 );

    virtual ~AbortedException();

public:
};

//***********************************************
class CLASS_DECLSPEC AlreadyConnectedException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    AlreadyConnectedException(  );

    explicit AlreadyConnectedException( LPVOID param0 );

    virtual ~AlreadyConnectedException();

public:
};

//***********************************************
class CLASS_DECLSPEC ApplicationFailedException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    ApplicationFailedException(  );

    ApplicationFailedException( LPTSTR param0 );

    explicit ApplicationFailedException( LPVOID param0 );

    virtual ~ApplicationFailedException();

public:
};

//***********************************************
class CLASS_DECLSPEC AsyncAlreadyStartedException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    AsyncAlreadyStartedException(  );

    explicit AsyncAlreadyStartedException( LPVOID param0 );

    virtual ~AsyncAlreadyStartedException();

public:
};

//***********************************************
class CLASS_DECLSPEC BadCommandException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    BadCommandException(  );

    BadCommandException( LPTSTR param0 );

    explicit BadCommandException( LPVOID param0 );

    virtual ~BadCommandException();

public:
};

//***********************************************
class CLASS_DECLSPEC ClassLoadException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    ClassLoadException(  );

    explicit ClassLoadException( LPVOID param0 );

    virtual ~ClassLoadException();

public:
};

//***********************************************
class CLASS_DECLSPEC CommunicationException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    CommunicationException(  );

    CommunicationException( LPTSTR param0 );

    explicit CommunicationException( LPVOID param0 );

    virtual ~CommunicationException();

public:
};

//***********************************************
class CLASS_DECLSPEC ConnectFailedException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    ConnectFailedException(  );

    ConnectFailedException( LPTSTR param0 );

    explicit ConnectFailedException( LPVOID param0 );

    virtual ~ConnectFailedException();

public:
};

//***********************************************
class CLASS_DECLSPEC DataFormatException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    DataFormatException(  );

    explicit DataFormatException( LPVOID param0 );

    virtual ~DataFormatException();

public:
};

//***********************************************
class CLASS_DECLSPEC DeviceLockedException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    DeviceLockedException(  );

    DeviceLockedException( LPTSTR param0 );

    explicit DeviceLockedException( LPVOID param0 );

    virtual ~DeviceLockedException();

public:
};

//***********************************************
class CLASS_DECLSPEC DisconnectFailedException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    DisconnectFailedException(  );

    explicit DisconnectFailedException( LPVOID param0 );

    virtual ~DisconnectFailedException();

public:
};

//***********************************************
class CLASS_DECLSPEC DistanceSetException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    DistanceSetException(  );

    DistanceSetException( LPTSTR param0 );

    explicit DistanceSetException( LPVOID param0 );

    virtual ~DistanceSetException();

public:
};

//***********************************************
class CLASS_DECLSPEC DoubleFaultException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    DoubleFaultException(  );

    DoubleFaultException( LPTSTR param0 );

    explicit DoubleFaultException( LPVOID param0 );

    virtual ~DoubleFaultException();

public:
};

//***********************************************
class CLASS_DECLSPEC FileAccessException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    FileAccessException(  );

    FileAccessException( LPTSTR param0 );

    explicit FileAccessException( LPVOID param0 );

    virtual ~FileAccessException();

public:
};

//***********************************************
class CLASS_DECLSPEC InterfaceBusyException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    InterfaceBusyException(  );

    InterfaceBusyException( LPTSTR param0 );

    explicit InterfaceBusyException( LPVOID param0 );

    virtual ~InterfaceBusyException();

public:
};

//***********************************************
class CLASS_DECLSPEC InternalDeviceFailureException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    InternalDeviceFailureException(  );

    InternalDeviceFailureException( LPTSTR param0 );

    explicit InternalDeviceFailureException( LPVOID param0 );

    virtual ~InternalDeviceFailureException();

public:
};

//***********************************************
class CLASS_DECLSPEC InternalTrackerException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    InternalTrackerException(  );

    InternalTrackerException( LPTSTR param0 );

    explicit InternalTrackerException( LPVOID param0 );

    virtual ~InternalTrackerException();

public:
};

//***********************************************
class CLASS_DECLSPEC LaserStateException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    LaserStateException(  );

    LaserStateException( LPTSTR param0 );

    explicit LaserStateException( LPVOID param0 );

    virtual ~LaserStateException();

public:
};

//***********************************************
class CLASS_DECLSPEC MeasureTypeException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    MeasureTypeException(  );

    explicit MeasureTypeException( LPVOID param0 );

    virtual ~MeasureTypeException();

public:
};

//***********************************************
class CLASS_DECLSPEC MotorStateException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    MotorStateException(  );

    MotorStateException( LPTSTR param0 );

    explicit MotorStateException( LPVOID param0 );

    virtual ~MotorStateException();

public:
};

//***********************************************
class CLASS_DECLSPEC NoDataAvailableException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    NoDataAvailableException(  );

    explicit NoDataAvailableException( LPVOID param0 );

    virtual ~NoDataAvailableException();

public:
};

//***********************************************
class CLASS_DECLSPEC NoResponseException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    NoResponseException(  );

    explicit NoResponseException( LPVOID param0 );

    virtual ~NoResponseException();

public:
};

//***********************************************
class CLASS_DECLSPEC NoTargetException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    NoTargetException(  );

    NoTargetException( LPTSTR param0 );

    explicit NoTargetException( LPVOID param0 );

    virtual ~NoTargetException();

public:
};

//***********************************************
class CLASS_DECLSPEC NotConnectedException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    NotConnectedException(  );

    explicit NotConnectedException( LPVOID param0 );

    virtual ~NotConnectedException();

public:
};

//***********************************************
class CLASS_DECLSPEC PermissionException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    PermissionException(  );

    PermissionException( LPTSTR param0 );

    explicit PermissionException( LPVOID param0 );

    virtual ~PermissionException();

public:
};

//***********************************************
class CLASS_DECLSPEC RequestException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    RequestException(  );

    RequestException( LPTSTR param0 );

    explicit RequestException( LPVOID param0 );

    virtual ~RequestException();

public:
};

//***********************************************
class CLASS_DECLSPEC ShutterStateException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    ShutterStateException(  );

    ShutterStateException( LPTSTR param0 );

    explicit ShutterStateException( LPVOID param0 );

    virtual ~ShutterStateException();

public:
};

//***********************************************
class CLASS_DECLSPEC TrackingStateException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    TrackingStateException(  );

    TrackingStateException( LPTSTR param0 );

    explicit TrackingStateException( LPVOID param0 );

    virtual ~TrackingStateException();

public:
};

//***********************************************
class CLASS_DECLSPEC UnsupportedFeatureException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    UnsupportedFeatureException(  );

    UnsupportedFeatureException( LPTSTR param0 );

    explicit UnsupportedFeatureException( LPVOID param0 );

    virtual ~UnsupportedFeatureException();

public:
};

//***********************************************
class CLASS_DECLSPEC UserEntryException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    UserEntryException(  );

    UserEntryException( LPTSTR param0 );

    explicit UserEntryException( LPVOID param0 );

    virtual ~UserEntryException();

public:
};

//***********************************************
class CLASS_DECLSPEC UserPromptException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    UserPromptException(  );

    UserPromptException( LPTSTR param0 );

    explicit UserPromptException( LPVOID param0 );

    virtual ~UserPromptException();

public:
};

//***********************************************
class CLASS_DECLSPEC CustomPortsException: public TrackerException
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:
    virtual void throwThisException();
public:

    CustomPortsException(  );

    CustomPortsException( LPTSTR param0 );

    explicit CustomPortsException( LPVOID param0 );

    virtual ~CustomPortsException();

public:
};

//***********************************************
class CLASS_DECLSPEC SMXObject: public BaseDriverObject

{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    SMXObject(  );

    explicit SMXObject( LPVOID param0 );

    virtual ~SMXObject();

    static SMXObject * createInstance( LPVOID envVoid, LPVOID objVoid );

public:
};

//***********************************************
class CLASS_DECLSPEC Boolean: public SMXObject
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    Boolean( bool param0 );

    Boolean( LPTSTR param0 );

    explicit Boolean( LPVOID param0 );

    virtual ~Boolean();

    bool equals( SMXObject * param0 );

    LPTSTR toString(  );

    LPTSTR toString( bool param0 );

    int hashCode( bool param0 );

    int hashCode(  );

    int compareTo( Boolean * param0 );

    int compareTo( SMXObject * param0 );

    bool getBoolean( LPTSTR param0 );

    bool booleanValue(  );

    Boolean * valueOf( bool param0 );

    Boolean * valueOf( LPTSTR param0 );

    int compare( bool param0, bool param1 );

    bool logicalAnd( bool param0, bool param1 );

    bool logicalOr( bool param0, bool param1 );

    bool logicalXor( bool param0, bool param1 );

    bool parseBoolean( LPTSTR param0 );

public:
};

//***********************************************
class CLASS_DECLSPEC ApplicationResults: public SMXObject
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    ApplicationResults( LPTSTR param0, long param1 );

    ApplicationResults( LPTSTR param0, LPTSTR param1, long param2 );

    explicit ApplicationResults( LPVOID param0 );

    virtual ~ApplicationResults();

    LPTSTR getResult(  );

    long getTime(  );

    LPTSTR getDetails(  );

public:
};

//***********************************************
class CLASS_DECLSPEC DistanceMode: public SMXObject
{
public:
    virtual LPVOID getJavaInstance() = 0;

    static DistanceMode * createInstance( LPVOID envVoid, LPVOID objVoid );

public:
};

//***********************************************
class CLASS_DECLSPEC ADMOnly: public DistanceMode
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    ADMOnly(  );

    explicit ADMOnly( LPVOID param0 );

    virtual ~ADMOnly();

public:
};

//***********************************************
class CLASS_DECLSPEC InterferometerOnly: public DistanceMode
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    InterferometerOnly(  );

    explicit InterferometerOnly( LPVOID param0 );

    virtual ~InterferometerOnly();

public:
};

//***********************************************
class CLASS_DECLSPEC InterferometerSetByADM: public DistanceMode
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    InterferometerSetByADM(  );

    explicit InterferometerSetByADM( LPVOID param0 );

    virtual ~InterferometerSetByADM();

public:
};

//***********************************************
class CLASS_DECLSPEC UserSpecifiedDistance: public DistanceMode
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    UserSpecifiedDistance(  );

    explicit UserSpecifiedDistance( LPVOID param0 );

    virtual ~UserSpecifiedDistance();

public:
};

//***********************************************
class CLASS_DECLSPEC StartTrigger
{
public:
    virtual LPVOID getJavaInstance() = 0;

    static StartTrigger * createInstance( LPVOID envVoid, LPVOID objVoid );

public:
};

//***********************************************
class CLASS_DECLSPEC ExternalStartTrigger: public StartTrigger
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    ExternalStartTrigger(  );

    explicit ExternalStartTrigger( LPVOID param0 );

    virtual ~ExternalStartTrigger();

    bool equals( StartTrigger * param0 );

public:
};

//***********************************************
class CLASS_DECLSPEC NullStartTrigger: public StartTrigger
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    NullStartTrigger(  );

    explicit NullStartTrigger( LPVOID param0 );

    virtual ~NullStartTrigger();

    bool equals( StartTrigger * param0 );

public:
};

//***********************************************
class CLASS_DECLSPEC ContinueTrigger
{
public:
    virtual LPVOID getJavaInstance() = 0;

    static ContinueTrigger * createInstance( LPVOID envVoid, LPVOID objVoid );

public:
};

//***********************************************
class CLASS_DECLSPEC NullContinueTrigger: public ContinueTrigger
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    NullContinueTrigger(  );

    explicit NullContinueTrigger( LPVOID param0 );

    virtual ~NullContinueTrigger();

    bool equals( ContinueTrigger * param0 );

public:
};

//***********************************************
class CLASS_DECLSPEC DistanceTrigger: public ContinueTrigger
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    DistanceTrigger( double param0 );

    explicit DistanceTrigger( LPVOID param0 );

    virtual ~DistanceTrigger();

    bool equals( ContinueTrigger * param0 );

    void setDistance( double param0 );

    double getDistance(  );

public:
};

//***********************************************
class CLASS_DECLSPEC IntervalTrigger: public ContinueTrigger
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    IntervalTrigger( double param0 );

    explicit IntervalTrigger( LPVOID param0 );

    virtual ~IntervalTrigger();

    bool equals( ContinueTrigger * param0 );

    void setObservationRate( double param0 );

    double getObservationRate(  );

public:
};

//***********************************************
class CLASS_DECLSPEC ExternalContinueTrigger: public ContinueTrigger
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    ExternalContinueTrigger(  );

    explicit ExternalContinueTrigger( LPVOID param0 );

    virtual ~ExternalContinueTrigger();

    bool equals( ContinueTrigger * param0 );

public:
};

//***********************************************
class CLASS_DECLSPEC AsyncMsg: public BaseDriverObject

{
public:
    virtual LPVOID getJavaInstance() = 0;

    static AsyncMsg * createInstance( LPVOID envVoid, LPVOID objVoid );

public:
};

//***********************************************
class CLASS_DECLSPEC Diagnostic: public AsyncMsg
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    Diagnostic( int param0, double param1, int param2, LPTSTR param3 );

    explicit Diagnostic( LPVOID param0 );

    virtual ~Diagnostic();

    int getID(  );

    int getCode(  );

    double getTimeStamp(  );

    LPTSTR getTrackerSpecifics(  );

public:
    static const int UNKNOWN; /* 0 */
    static const int POSITION_FAILURE; /* 1 */
    static const int DEVICE_RESET; /* 2 */
    static const int DEVICE_FAILED; /* 3 */
    static const int REAL_TIME_CLOCK_RESET; /* 4 */
    static const int REAL_TIME_CLOCK_NOT_SET; /* 5 */
    static const int DEFAULT_CONFIGURATION_LOADED; /* 6 */
    static const int NO_ENCODER_MAPS; /* 7 */
    static const int INTERNAL_FAILURE; /* 8 */
};

//***********************************************
class CLASS_DECLSPEC Status: public AsyncMsg
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    Status( int param0, bool param1, double param2, int param3, LPTSTR param4 );

    explicit Status( LPVOID param0 );

    virtual ~Status();

    bool getState(  );

    int getID(  );

    int getCode(  );

    double getTimeStamp(  );

    LPTSTR getTrackerSpecifics(  );

public:
    static const int UNKNOWN; /* 0 */
    static const int MEASURING; /* 1 */
    static const int NEED_DISTANCE_RESET; /* 2 */
    static const int LASER_NOT_LOCKED; /* 3 */
    static const int ISOLATOR_OUT_OF_RANGE; /* 4 */
    static const int BAD_WEATHER_DATA; /* 5 */
    static const int MOTORS_OFF; /* 6 */
    static const int MARGINAL_TARGET; /* 7 */
    static const int IFM_DROPOUT; /* 8 */
    static const int ADM_DROPOUT; /* 9 */
    static const int HIGH_RADIAL_SPEED; /* 10 */
    static const int NO_TARGET; /* 11 */
    static const int SEARCHING_FOR_TARGET; /* 12 */
    static const int SHUTTER_CLOSED; /* 13 */
    static const int LASER_OFF; /* 14 */
    static const int LEVEL_ENABLED; /* 15 */
    static const int MOTOR_POSITION_INACCURATE; /* 16 */
    static const int MANUAL_POSITION_CHANGE; /* 17 */
    static const int CLOCK_SET_PENDING; /* 18 */
    static const int CLOSE_TO_LOW_PHYSICAL_STOP; /* 19 */
    static const int CLOSE_TO_HIGH_PHYSICAL_STOP; /* 20 */
    static const int ADM_INACCURATE; /* 21 */
    static const int LICENSE_EXPIRED; /* 22 */
    static const int SMART_WARM_UP_IN_PROGRESS; /* 23 */
    static const int NEED_AUTO_ADJUST; /* 24 */
};

//***********************************************
class CLASS_DECLSPEC Alarm: public AsyncMsg
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    Alarm( int param0, bool param1, double param2, int param3, LPTSTR param4 );

    explicit Alarm( LPVOID param0 );

    virtual ~Alarm();

    bool getState(  );

    int getID(  );

    double getTimeStamp(  );

    int getAlarmNumber(  );

    LPTSTR getTrackerSpecifics(  );

public:
};

//***********************************************
class CLASS_DECLSPEC Change: public AsyncMsg
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    Change( int param0, double param1, int param2, LPTSTR param3, SMXObject * param4 );

    explicit Change( LPVOID param0 );

    virtual ~Change();

    int getID(  );

    int getCode(  );

    double getTimeStamp(  );

    SMXObject * getRelatedData(  );

    LPTSTR getTrackerSpecifics(  );

public:
    static const int UNKNOWN; /* 0 */
    static const int SIGHT_ORIENTATION; /* 1 */
    static const int TRACKING_MODE; /* 2 */
    static const int DISTANCE_MODE; /* 3 */
    static const int TARGET_TYPE; /* 4 */
    static const int PROBE_CONNECTED; /* 5 */
    static const int PROBE_CHANGE; /* 6 */
    static const int PROBE_BATTERY_STATE_CHANGE; /* 7 */
    static const int TRACKER_BATTERY_1_STATE_CHANGE; /* 9 */
    static const int TRACKER_BATTERY_2_STATE_CHANGE; /* 10 */
    static const int RUN_AUTO_COMP; /* 11 */
    static const int NEED_HOME; /* 12 */
    static const int PROBE_KINEMATIC_DISCONNECTED; /* 13 */
};

//***********************************************
class CLASS_DECLSPEC Filter
{
public:
    virtual LPVOID getJavaInstance() = 0;

    static Filter * createInstance( LPVOID envVoid, LPVOID objVoid );

public:
};

//***********************************************
class CLASS_DECLSPEC NullFilter: public Filter
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    NullFilter(  );

    explicit NullFilter( LPVOID param0 );

    virtual ~NullFilter();

    bool equals( Filter * param0 );

public:
};

//***********************************************
class CLASS_DECLSPEC AverageFilter: public Filter
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    AverageFilter(  );

    explicit AverageFilter( LPVOID param0 );

    virtual ~AverageFilter();

    bool equals( Filter * param0 );

public:
};

//***********************************************
class CLASS_DECLSPEC StdDevFilter: public Filter
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    StdDevFilter(  );

    explicit StdDevFilter( LPVOID param0 );

    virtual ~StdDevFilter();

    bool equals( Filter * param0 );

public:
};

//***********************************************
class CLASS_DECLSPEC AdaptiveFilter: public Filter
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    AdaptiveFilter( double param0 );

    explicit AdaptiveFilter( LPVOID param0 );

    virtual ~AdaptiveFilter();

    bool equals( Filter * param0 );

    double getSdm(  );

    void setSdm( double param0 );

public:
};

//***********************************************
class CLASS_DECLSPEC InterpolationFilter: public Filter
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    InterpolationFilter(  );

    explicit InterpolationFilter( LPVOID param0 );

    virtual ~InterpolationFilter();

    bool equals( Filter * param0 );

public:
};

//***********************************************
class CLASS_DECLSPEC MeasurePointStats
{
public:
    virtual LPVOID getJavaInstance() = 0;

    static MeasurePointStats * createInstance( LPVOID envVoid, LPVOID objVoid );

public:
};

//***********************************************
class CLASS_DECLSPEC MeasurePointStdDev: public MeasurePointStats
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit MeasurePointStdDev( LPVOID param0 );

    virtual ~MeasurePointStdDev();

    double zenithStdDev(  );

    double distanceStdDev(  );

    double rotationAStdDev(  );

    double rotationBStdDev(  );

    double azimuthStdDev(  );

    double rotationCStdDev(  );

public:
};

//***********************************************
class CLASS_DECLSPEC MeasurePointData: public BaseDriverObject

{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit MeasurePointData( LPVOID param0 );

    virtual ~MeasurePointData();

    int status(  );

    double time(  );

    double distance(  );

    double zenith(  );

    double azimuth(  );

    double rotationA(  );

    double rotationB(  );

    double rotationC(  );

    bool sixDofData(  );

    MeasurePointStats * statistics(  );

public:
    static const int DATA_ACCURATE; /* 0 */
    static const int DATA_INACCURATE; /* 1 */
    static const int DATA_ERROR; /* 2 */
};

//***********************************************
class CLASS_DECLSPEC MPEResultsData: public BaseDriverObject

{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit MPEResultsData( LPVOID param0 );

    virtual ~MPEResultsData();

    double error(  );

    double mpe(  );

    bool meetsTrackerSpecification(  );

    double errorAsPercentageMPE(  );

public:
};

//***********************************************
class CLASS_DECLSPEC SimplePointPairData
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    SimplePointPairData( double param0, double param1, double param2, double param3, double param4, double param5 );

    explicit SimplePointPairData( LPVOID param0 );

    virtual ~SimplePointPairData();

    double getSecondPointZenith(  );

    double getSecondPointDistance(  );

    double getSecondPointAzimuth(  );

    double getFirstPointZenith(  );

    double getFirstPointDistance(  );

    double getFirstPointAzimuth(  );

public:
};

//***********************************************
class CLASS_DECLSPEC MaterialTemperatureData
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit MaterialTemperatureData( LPVOID param0 );

    virtual ~MaterialTemperatureData();

    int numSensors(  );

    double temperature(  );

public:
};

//***********************************************
class CLASS_DECLSPEC LevelData
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit LevelData( LPVOID param0 );

    virtual ~LevelData();

    double getRY(  );

    double getRZ(  );

    double getRX(  );

public:
};

//***********************************************
class CLASS_DECLSPEC MeasureCfg
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    MeasureCfg( int param0, Filter * param1, StartTrigger * param2, ContinueTrigger * param3 );

    explicit MeasureCfg( LPVOID param0 );

    virtual ~MeasureCfg();

    void setFilter( Filter * param0 );

    StartTrigger * getStartTrigger(  );

    Filter * getFilter(  );

    void setStartTrigger( StartTrigger * param0 );

    ContinueTrigger * getContinueTrigger(  );

    int getSamplesPerObservation(  );

    void setSamplesPerObservation( int param0 );

    void setContinueTrigger( ContinueTrigger * param0 );

public:
};

//***********************************************
class CLASS_DECLSPEC TrackerInterface
{
public:
    virtual LPVOID getJavaInstance() = 0;

public:
};

//***********************************************
class CLASS_DECLSPEC TargetType: public SMXObject
{
public:
    virtual LPVOID getJavaInstance() = 0;

    static TargetType * createInstance( LPVOID envVoid, LPVOID objVoid );

public:
};

//***********************************************
class CLASS_DECLSPEC SMRTargetType: public TargetType
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    SMRTargetType( double param0 );

    explicit SMRTargetType( LPVOID param0 );

    virtual ~SMRTargetType();

    double getDiameter(  );

public:
};

//***********************************************
class CLASS_DECLSPEC MirrorTargetType: public TargetType
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    MirrorTargetType(  );

    explicit MirrorTargetType( LPVOID param0 );

    virtual ~MirrorTargetType();

public:
};

//***********************************************
class CLASS_DECLSPEC WindowedSMRTargetType: public TargetType
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    WindowedSMRTargetType( double param0 );

    explicit WindowedSMRTargetType( LPVOID param0 );

    virtual ~WindowedSMRTargetType();

    double getDiameter(  );

    double getRadiusOffset( DistanceMode * param0 );

public:
};

//***********************************************
class CLASS_DECLSPEC SixDofTargetType: public TargetType
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    SixDofTargetType(  );

    explicit SixDofTargetType( LPVOID param0 );

    virtual ~SixDofTargetType();

public:
};

//***********************************************
class CLASS_DECLSPEC CatEyeTargetType: public TargetType
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    CatEyeTargetType( double param0, double param1 );

    explicit CatEyeTargetType( LPVOID param0 );

    virtual ~CatEyeTargetType();

    double getOffset(  );

    double getDiameter(  );

public:
};

//***********************************************
class CLASS_DECLSPEC AlarmType
{
public:
    virtual LPVOID getJavaInstance() = 0;

    static AlarmType * createInstance( LPVOID envVoid, LPVOID objVoid );

public:
};

//***********************************************
class CLASS_DECLSPEC DeviationAlarm: public AlarmType
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    DeviationAlarm( double param0, double param1 );

    explicit DeviationAlarm( LPVOID param0 );

    virtual ~DeviationAlarm();

    double getDeviation(  );

    double getSetPoint(  );

public:
};

//***********************************************
class CLASS_DECLSPEC HighAlarm: public AlarmType
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    HighAlarm( double param0 );

    explicit HighAlarm( LPVOID param0 );

    virtual ~HighAlarm();

    double getSetPoint(  );

public:
};

//***********************************************
class CLASS_DECLSPEC LowAlarm: public AlarmType
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    LowAlarm( double param0 );

    explicit LowAlarm( LPVOID param0 );

    virtual ~LowAlarm();

    double getSetPoint(  );

public:
};

//***********************************************
class CLASS_DECLSPEC NullAlarm: public AlarmType
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    NullAlarm(  );

    explicit NullAlarm( LPVOID param0 );

    virtual ~NullAlarm();

public:
};

//***********************************************
class CLASS_DECLSPEC ExtTempType
{
public:
    virtual LPVOID getJavaInstance() = 0;

    static ExtTempType * createInstance( LPVOID envVoid, LPVOID objVoid );

public:
};

//***********************************************
class CLASS_DECLSPEC NullExtTemp: public ExtTempType
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    NullExtTemp(  );

    explicit NullExtTemp( LPVOID param0 );

    virtual ~NullExtTemp();

public:
};

//***********************************************
class CLASS_DECLSPEC AirExtTemp: public ExtTempType
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    AirExtTemp(  );

    explicit AirExtTemp( LPVOID param0 );

    virtual ~AirExtTemp();

public:
};

//***********************************************
class CLASS_DECLSPEC MaterialExtTemp: public ExtTempType
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    MaterialExtTemp(  );

    explicit MaterialExtTemp( LPVOID param0 );

    virtual ~MaterialExtTemp();

public:
};

//***********************************************
class CLASS_DECLSPEC VersionInfo: public SMXObject
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit VersionInfo( LPVOID param0 );

    virtual ~VersionInfo();

    int buildNumber(  );

    int minorNumber(  );

    int majorNumber(  );

    int minorMinorNumber(  );

    LPTSTR specialStr(  );

public:
};

//***********************************************
class CLASS_DECLSPEC WeatherInformation: public SMXObject
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    WeatherInformation( double param0, double param1, double param2 );

    WeatherInformation( double param0, double param1, double param2, long param3, long param4, long param5 );

    explicit WeatherInformation( LPVOID param0 );

    virtual ~WeatherInformation();

    double getAirPressure(  );

    double getHumidity(  );

    double getAirTemperature(  );

    long getHumiditySource(  );

    long getAirPressureSource(  );

    long getAirTemperatureSource(  );

public:
};

//***********************************************
class CLASS_DECLSPEC CommandCompleteEvent
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit CommandCompleteEvent( LPVOID param0 );

    virtual ~CommandCompleteEvent();

    TrackerException * getRelatedException(  );

public:
};

//***********************************************
class CLASS_DECLSPEC ConnectEvent
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit ConnectEvent( LPVOID param0 );

    virtual ~ConnectEvent();

    bool isConnected(  );

public:
};

//***********************************************
class CLASS_DECLSPEC MeasureDataEvent
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit MeasureDataEvent( LPVOID param0 );

    virtual ~MeasureDataEvent();

    int getNumMeasurements(  );

public:
};

//***********************************************
class CLASS_DECLSPEC BkndMeasureDataEvent
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit BkndMeasureDataEvent( LPVOID param0 );

    virtual ~BkndMeasureDataEvent();

    int getNumMeasurements(  );

public:
};

//***********************************************
class CLASS_DECLSPEC DiagnosticEvent
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit DiagnosticEvent( LPVOID param0 );

    virtual ~DiagnosticEvent();

    Diagnostic * getDiagnostic(  );

public:
};

//***********************************************
class CLASS_DECLSPEC StatusEvent
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit StatusEvent( LPVOID param0 );

    virtual ~StatusEvent();

    Status * getStatus(  );

public:
};

//***********************************************
class CLASS_DECLSPEC AlarmEvent
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit AlarmEvent( LPVOID param0 );

    virtual ~AlarmEvent();

    Alarm * getAlarm(  );

public:
};

//***********************************************
class CLASS_DECLSPEC ChangeEvent
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit ChangeEvent( LPVOID param0 );

    virtual ~ChangeEvent();

    Change * getChange(  );

public:
};

//***********************************************
class CLASS_DECLSPEC BusyEvent
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit BusyEvent( LPVOID param0 );

    virtual ~BusyEvent();

    bool getMeasureState(  );

    bool getCommandState(  );

    bool getBkndMeasureState(  );

public:
};

//***********************************************
class CLASS_DECLSPEC ApplicationEvent
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit ApplicationEvent( LPVOID param0 );

    virtual ~ApplicationEvent();

    LPTSTR getAppName(  );

    bool isAppRunning(  );

public:
};

//***********************************************
class CLASS_DECLSPEC ProbeButtonIndex
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit ProbeButtonIndex( LPVOID param0 );

    virtual ~ProbeButtonIndex();

public:
    static const int BUTTON_1; /* 0 */
    static const int BUTTON_2; /* 1 */
    static const int BUTTON_3; /* 2 */
    static const int BUTTON_4; /* 3 */
};

//***********************************************
class CLASS_DECLSPEC ProbeButtonStatus
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit ProbeButtonStatus( LPVOID param0 );

    virtual ~ProbeButtonStatus();

public:
    static const int OFF; /* 0 */
    static const int ON; /* 1 */
};

//***********************************************
class CLASS_DECLSPEC ProbeButtonEvent
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit ProbeButtonEvent( LPVOID param0 );

    virtual ~ProbeButtonEvent();

    int getId(  );

    int getStatus(  );

public:
};

//***********************************************
class CLASS_DECLSPEC AvailableEvent
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit AvailableEvent( LPVOID param0 );

    virtual ~AvailableEvent();

    bool isAvailable(  );

public:
};

//***********************************************
class CLASS_DECLSPEC SmartWarmupWaitState
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit SmartWarmupWaitState( LPVOID param0 );

    virtual ~SmartWarmupWaitState();

public:
    static const int DONE; /* 0 */
    static const int EXTENDED; /* 1 */
    static const int LONG; /* 2 */
    static const int SHORT; /* 3 */
    static const int QUICK; /* 4 */
};

//***********************************************
class CLASS_DECLSPEC AlarmIndex
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit AlarmIndex( LPVOID param0 );

    virtual ~AlarmIndex();

public:
    static const int BATTERY_1; /* 1 */
    static const int BATTERY_2; /* 2 */
    static const int EXT_TEMP_1; /* 3 */
    static const int PROBE_BATTERY; /* 4 */
};

//***********************************************
class CLASS_DECLSPEC BatteryState: public SMXObject
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit BatteryState( LPVOID param0 );

    virtual ~BatteryState();

    int getBatteryState(  );

public:
    static const int ACCURATE; /* 0 */
    static const int INACCURATE; /* 1 */
    static const int WARNING; /* 2 */
    static const int CRITICAL; /* 3 */
    static const int NOT_PRESENT; /* 4 */
};

//***********************************************
class CLASS_DECLSPEC Probe: public SMXObject
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    Probe( LPTSTR param0, LPTSTR param1, double param2, double param3, double param4, double param5, double param6, double param7, int param8, int param9, double param10, int param11, int param12 );

    Probe( LPTSTR param0, LPTSTR param1, double param2, double param3 );

    Probe( LPTSTR param0, LPTSTR param1, double param2 );

    explicit Probe( LPVOID param0 );

    virtual ~Probe();

    int type(  );

    double getLength(  );

    LPTSTR getName(  );

    void setName( LPTSTR param0 );

    void setLength( double param0 );

    double getX(  );

    double getY(  );

    LPTSTR getSerialNumber(  );

    double getDiameter(  );

    bool compensated(  );

    LPTSTR getAdapterName(  );

    bool isErrorSupported(  );

    void setDiameter( double param0 );

    double getDateOfCalibration(  );

    double getError(  );

    bool active(  );

    double getZ(  );

    double getTemp(  );

public:
    static const int STANDARD; /* 0 */
    static const int CUSTOM; /* 1 */
    static const int KINEMATIC; /* 2 */
};

//***********************************************
class CLASS_DECLSPEC ProbeBatteryState: public SMXObject
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit ProbeBatteryState( LPVOID param0 );

    virtual ~ProbeBatteryState();

    int getBatteryState(  );

public:
    static const int ACCURATE; /* 0 */
    static const int INACCURATE; /* 1 */
    static const int ERROR_STATE; /* 2 */
};

//***********************************************
class CLASS_DECLSPEC AvailableTracker: public SMXObject
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    AvailableTracker( LPTSTR param0, LPTSTR param1, int param2, int param3 );

    explicit AvailableTracker( LPVOID param0 );

    virtual ~AvailableTracker();

    LPTSTR getSerialNum(  );

    LPTSTR getIpAddress(  );

    int getModelType(  );

    int getConnectionType(  );

public:
    static const int MODEL_FARO; /* 0 */
    static const int MODEL_VANTAGE; /* 1 */
    static const int MODEL_VANTAGE_S; /* 2 */
    static const int WIRED; /* 0 */
    static const int WIFI; /* 1 */
};

//***********************************************
class CLASS_DECLSPEC ConnectionType: public SMXObject
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    ConnectionType(  );

    explicit ConnectionType( LPVOID param0 );

    virtual ~ConnectionType();

public:
    static const int NONE; /* 0 */
    static const int WIRED; /* 1 */
    static const int WIFI; /* 2 */
    static const int INDETERMINATE; /* 3 */
};

//***********************************************
class CLASS_DECLSPEC AutomatedCompResult: public SMXObject
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    AutomatedCompResult(  );

    explicit AutomatedCompResult( LPVOID param0 );

    virtual ~AutomatedCompResult();

public:
    static const int PASS; /* 1 */
    static const int LEARN_TARGETS_PROCEDURE_NOT_RUN; /* 2 */
    static const int FAILED_TO_FIND_TARGET_1; /* 3 */
    static const int FAILED_TO_FIND_TARGET_2; /* 4 */
    static const int NO_TARGET_AT_HOME; /* 5 */
    static const int OUT_OF_SPEC; /* 6 */
};

//***********************************************
class CLASS_DECLSPEC ProbeModelType: public SMXObject
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    ProbeModelType(  );

    explicit ProbeModelType( LPVOID param0 );

    virtual ~ProbeModelType();

public:
    static const int NONE; /* 0 */
    static const int SIX_PROBE_1_0; /* 1 */
    static const int SIX_PROBE_2_0; /* 2 */
};

//***********************************************
class CLASS_DECLSPEC ProbeCompHistoryData: public SMXObject
{
private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    explicit ProbeCompHistoryData( LPVOID param0 );

    virtual ~ProbeCompHistoryData();

    bool inUse(  );

    double getX(  );

    double getY(  );

    double getTime(  );

    double getDiameter(  );

    double getError(  );

    double getZ(  );

    double getTemp(  );

public:
};
class CLASS_DECLSPEC CommandCompleteListener
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );

private:
    void addStaticPtr( LPVOID envPtr );
    static void JNICALL nativeCall( LPVOID env, LPVOID obj, LPVOID javaEvent, long peerPtr);
public:

    CommandCompleteListener(  );

    virtual ~CommandCompleteListener();

    virtual void commandComplete( CommandCompleteEvent * param0 ) = 0;
};
class CLASS_DECLSPEC ConnectListener
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );

private:
    void addStaticPtr( LPVOID envPtr );
    static void JNICALL nativeCall( LPVOID env, LPVOID obj, LPVOID javaEvent, long peerPtr);
public:

    ConnectListener(  );

    virtual ~ConnectListener();

    virtual void connectionChanged( ConnectEvent * param0 ) = 0;
};
class CLASS_DECLSPEC MeasureDataListener
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );

private:
    void addStaticPtr( LPVOID envPtr );
    static void JNICALL nativeCall( LPVOID env, LPVOID obj, LPVOID javaEvent, long peerPtr);
public:

    MeasureDataListener(  );

    virtual ~MeasureDataListener();

    virtual void dataAvailable( MeasureDataEvent * param0 ) = 0;
};
class CLASS_DECLSPEC BkndMeasureDataListener
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );

private:
    void addStaticPtr( LPVOID envPtr );
    static void JNICALL nativeCall( LPVOID env, LPVOID obj, LPVOID javaEvent, long peerPtr);
public:

    BkndMeasureDataListener(  );

    virtual ~BkndMeasureDataListener();

    virtual void dataAvailable( BkndMeasureDataEvent * param0 ) = 0;
};
class CLASS_DECLSPEC DiagnosticListener
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );

private:
    void addStaticPtr( LPVOID envPtr );
    static void JNICALL nativeCall( LPVOID env, LPVOID obj, LPVOID javaEvent, long peerPtr);
public:

    DiagnosticListener(  );

    virtual ~DiagnosticListener();

    virtual void diagnosticReported( DiagnosticEvent * param0 ) = 0;
};
class CLASS_DECLSPEC ChangeListener
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );

private:
    void addStaticPtr( LPVOID envPtr );
    static void JNICALL nativeCall( LPVOID env, LPVOID obj, LPVOID javaEvent, long peerPtr);
public:

    ChangeListener(  );

    virtual ~ChangeListener();

    virtual void changeOccurred( ChangeEvent * param0 ) = 0;
};
class CLASS_DECLSPEC StatusListener
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );

private:
    void addStaticPtr( LPVOID envPtr );
    static void JNICALL nativeCall( LPVOID env, LPVOID obj, LPVOID javaEvent, long peerPtr);
public:

    StatusListener(  );

    virtual ~StatusListener();

    virtual void statusChanged( StatusEvent * param0 ) = 0;
};
class CLASS_DECLSPEC AlarmListener
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );

private:
    void addStaticPtr( LPVOID envPtr );
    static void JNICALL nativeCall( LPVOID env, LPVOID obj, LPVOID javaEvent, long peerPtr);
public:

    AlarmListener(  );

    virtual ~AlarmListener();

    virtual void alarmChanged( AlarmEvent * param0 ) = 0;
};
class CLASS_DECLSPEC BusyListener
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );

private:
    void addStaticPtr( LPVOID envPtr );
    static void JNICALL nativeCall( LPVOID env, LPVOID obj, LPVOID javaEvent, long peerPtr);
public:

    BusyListener(  );

    virtual ~BusyListener();

    virtual void stateChanged( BusyEvent * param0 ) = 0;
};
class CLASS_DECLSPEC ApplicationListener
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );

private:
    void addStaticPtr( LPVOID envPtr );
    static void JNICALL nativeCall( LPVOID env, LPVOID obj, LPVOID javaEvent, long peerPtr);
public:

    ApplicationListener(  );

    virtual ~ApplicationListener();

    virtual void stateChanged( ApplicationEvent * param0 ) = 0;
};
class CLASS_DECLSPEC ProbeButtonListener
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );

private:
    void addStaticPtr( LPVOID envPtr );
    static void JNICALL nativeCall( LPVOID env, LPVOID obj, LPVOID javaEvent, long peerPtr);
public:

    ProbeButtonListener(  );

    virtual ~ProbeButtonListener();

    virtual void buttonStatusChanged( ProbeButtonEvent * param0 ) = 0;
};
class CLASS_DECLSPEC AvailableListener
{
protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );

private:
    void addStaticPtr( LPVOID envPtr );
    static void JNICALL nativeCall( LPVOID env, LPVOID obj, LPVOID javaEvent, long peerPtr);
public:

    AvailableListener(  );

    virtual ~AvailableListener();

    virtual void availabilityChanged( AvailableEvent * param0 ) = 0;
};

//***********************************************
class CLASS_DECLSPEC Tracker
{
private:
    static void JNICALL nativeCall( LPVOID env, LPVOID obj, LPVOID appName, bool flag);

protected:
    LPVOID globalInstance;

public:
    LPVOID getJavaInstance();

private:
    LPVOID globalClass;

    void setupGlobalClass( LPVOID envPtr );
public:

    Tracker( LPTSTR param0 );

    Tracker( TrackerInterface * param0 );

    Tracker( LPTSTR param0, int param1, int param2 );

    explicit Tracker( LPVOID param0 );

    virtual ~Tracker();

    void connect( LPTSTR param0, LPTSTR param1, LPTSTR param2 );

    void connect(  );

    bool initialized(  );

    bool initialized( bool param0 );

    void search( double param0, double param1, int param2 );

    void search( double param0, double param1 );

    void search( double param0 );

    void search( double param0, int param1 );

    void initialize( bool param0 );

    void initialize(  );

    VersionInfo * version(  );

    void readFile( LPTSTR param0, LPTSTR param1 );

    void abort(  );

    bool connected(  );

    void disconnect(  );

    void addChangeListener( ChangeListener * param0 );

    void move( double param0, double param1, double param2, bool param3, bool param4 );

    void move( double param0, double param1, double param2, bool param3 );

    void removeChangeListener( ChangeListener * param0 );

    TargetType * targetType(  );

    void setDelayFromPassiveToActiveFollowMe( double param0 );

    double getDelayFromPassiveToActiveFollowMe(  );

    bool probeBatteryStateChangeEventSupported(  );

    bool sixDofCapable(  );

    void initializeSmart( bool param0 );

    void initializeSmart(  );

    void changeMotorState( bool param0 );

    void changeTargetType( TargetType * param0 );

    int sampleRate(  );

    void stopMeasurePoint(  );

    void startAsync(  );

    void stopAsync(  );

    void readFileAbort(  );

    bool trackingOn(  );

    void writeFileAbort(  );

    bool admCapable(  );

    WeatherInformation * getWeatherInfo(  );

    bool adminPrivilege(  );

    LPTSTR getSerialNumber(  );

    void startSlew( double param0, double param1, double param2 );

    void startSlew( double param0, double param1 );

    bool admOnlyCapable(  );

    void releaseLock(  );

    bool wirelessCapable(  );

    bool targetPresent(  );

    LevelData * measureLevel(  );

    bool videoCapable(  );

    void comboSearch( double param0, double param1, double param2, double param3, double param4, bool param5 );

    void comboSearch(  );

    void comboSearch( double param0, double param1, bool param2 );

    void comboSearch( double param0, double param1, double param2, bool param3 );

    TrkDrvObjectArray * statusHistory(  );

    bool factoryPrivilege(  );

    LPTSTR getIPAddress(  );

    ExtTempType * externalTempType( int param0 );

    bool admScanCapable(  );

    bool gesturesCapable(  );

    bool isAACNoUICapable(  );

    void writeFile( LPTSTR param0, LPTSTR param1 );

    bool levelCapable(  );

    void resetCameras(  );

    void changeAlarmCfg( int param0, AlarmType * param1 );

    int batteryState( int param0 );

    bool powerButtonState(  );

    TrkDrvObjectArray * alarmHistory(  );

    void changeDistanceMeasureMode( DistanceMode * param0 );

    void changeFollowMeSearchRadius( double param0 );

    bool wirelessStateChangeSupported(  );

    void changeAirPressureToManual( double param0 );

    bool isQuickCompensationNoUICapable(  );

    int probeBatteryChargeRemaining(  );

    bool didAACPassSinceInitialization(  );

    void removeCompFromProbeCompHistory( Probe * param0, double param1 );

    void useCompFromProbeCompHistory( Probe * param0, double param1 );

    bool trackerBatteryEventCapable(  );

    bool autoCompRequired(  );

    bool autoCompCapable(  );

    void changeProbe( Probe * param0, bool param1 );

    LPTSTR probeAdapter(  );

    int connectionType(  );

    void modifyProbe( Probe * param0 );

    bool isFollowMeOn(  );

    TrkDrvObjectArray * probeCompHistory( Probe * param0 );

    bool sixProbe2Capable(  );

    bool wirelessOn(  );

    int runAutomatedComp(  );

    bool homeRequired(  );

    int probeModelType(  );

    TrkDrvObjectArray * availableProbes(  );

    void removeProbe( Probe * param0 );

    bool sixDofEnabled(  );

    void startMeasurePoint( MeasureCfg * param0 );

    void startBkndMeasurePoint( MeasureCfg * param0 );

    void toggleSightOrientation(  );

    TrkDrvObjectArray * diagnosticHistory(  );

    bool interferometerCapable(  );

    bool backsightOrientation(  );

    TrkDrvObjectArray * startedApplications(  );

    void changeTrackingState( bool param0 );

    void changeExternalTempType( int param0, ExtTempType * param1 );

    bool targetLocationValid(  );

    DistanceMode * distanceMeasureMode(  );

    TrkDrvObjectArray * availableApplications(  );

    void stopBkndMeasurePoint(  );

    int numExternalTempSensors(  );

    void modifyApplication( LPTSTR param0, LPTSTR param1 );

    TrkDrvObjectArray * readMeasurePointData( int param0 );

    MeasurePointData * readMeasurePointData(  );

    MeasurePointData * readBkndMeasurePointData(  );

    TrkDrvObjectArray * readBkndMeasurePointData( int param0 );

    bool isFollowMeCapable(  );

    void changeSixDofEnableState( bool param0 );

    bool isCatEyeTargetCapable(  );

    bool autoReconnectCapable(  );

    double getFollowMeSearchRadius(  );

    int smartWarmupWaitState(  );

    bool probeCompHistoryCapable(  );

    bool isResultReportingCapable(  );

    MPEResultsData * checkADMAgainstIFM( SimplePointPairData * param0 );

    bool standardPrivilege(  );

    bool isAdaptiveFilterCapable(  );

    bool readyToInitialize( bool param0 );

    void changeHumidityToManual( double param0 );

    bool gestureRecognitionOn(  );

    void searchUsingCamera(  );

    void changePowerButtonState( bool param0 );

    int batteryChargeRemaining( int param0 );

    TrkDrvObjectArray * availableTargetType(  );

    void changeGestureState( bool param0 );

    int applicationExitCode( LPTSTR param0 );

    ApplicationResults * applicationResults( LPTSTR param0 );

    bool probeAdapterConnected(  );

    int probeBatteryState(  );

    void changeWirelessState( bool param0 );

    void changeHumidityToHardware(  );

    void changeFollowMeState( bool param0 );

    void home( bool param0 );

    bool home( bool param0, bool param1 );

    AlarmType * alarmCfg( int param0 );

    bool motorsOn(  );

    void stopSlew(  );

    void reboot(  );

    void addProbe( Probe * param0 );

    Probe * probe(  );

    bool externalTempTypeChangeable(  );

    void changeAirTemperatureToHardware(  );

    double measureExternalTempSensor( int param0 );

    bool is_7_8_WindowedSMRTargetCapable(  );

    MaterialTemperatureData * measureMaterialTemperature(  );

    bool is_1_5_WindowedSMRTargetCapable(  );

    MPEResultsData * checkAngularAccuracyError( SimplePointPairData * param0 );

    bool isSelfCompensationNoUICapable(  );

    void changeAirPressureToHardware(  );

    void changeAirTemperatureToManual( double param0 );

    bool busy(  );

    bool exclusiveAccessForCurrentThread(  );

    bool isNoUIAACWithCompensationOptionSupported(  );

    bool measureInProgress(  );

    LevelData * readBufferedLevel(  );

    void startApplicationFrame( LPTSTR param0, LPTSTR param1 );

    void stopApplicationFrame( LPTSTR param0, bool param1 );

    void stopApplicationFrame( LPTSTR param0 );

    void setBkndMeasureBlocking( bool param0 );

    void setExclusiveAccess(  );

    void clearExclusiveAccess(  );

    void addConnectListener( ConnectListener * param0 );

    void setMeasureEventRate( int param0 );

    bool bkndMeasureInProgress(  );

    TrkDrvObjectArray * readBufferedAlarmHistory(  );

    int getMeasureEventRate(  );

    bool getBkndMeasureBlocking(  );

    void setBkndMeasureEventRate( int param0 );

    int getBkndMeasureEventRate(  );

    bool exclusiveAccessSet(  );

    bool busyForCurrentThread(  );

    void addProbeButtonListener( ProbeButtonListener * param0 );

    void addApplicationListener( ApplicationListener * param0 );

    void removeBusyListener( BusyListener * param0 );

    void addMeasureDataListener( MeasureDataListener * param0 );

    void addDiagnosticListener( DiagnosticListener * param0 );

    void addStatusListener( StatusListener * param0 );

    void removeDiagnosticListener( DiagnosticListener * param0 );

    void removeStatusListener( StatusListener * param0 );

    void removeAlarmListener( AlarmListener * param0 );

    static TrkDrvObjectArray * availableTrackers(  );

    void runNoUISelfCompensation(  );

    int availableMeasurements(  );

    void addAvailableListener( AvailableListener * param0 );

    void removeAvailableListener( AvailableListener * param0 );

    void removeConnectListener( ConnectListener * param0 );

    void runNoUIQuickCompensation(  );

    bool getBlocking(  );

    void setBlocking( bool param0 );

    bool asyncStarted(  );

    void addAlarmListener( AlarmListener * param0 );

    LPTSTR getTrackerType(  );

    void runNoUIAAC(  );

    void runNoUIAAC( LPTSTR param0 );

    void addBusyListener( BusyListener * param0 );

    bool abortNoUIAAC(  );

    void removeCommandCompleteListener( CommandCompleteListener * param0 );

    void availableBkndMeasurements(  );

    bool abortNoUISelfCompensation(  );

    void removeProbeButtonListener( ProbeButtonListener * param0 );

    bool abortNoUIQuickCompensation(  );

    void removeApplicationListener( ApplicationListener * param0 );

    void removeMeasureDataListener( MeasureDataListener * param0 );

    void startApplicationFrameAlwaysOnTop( LPTSTR param0, LPTSTR param1 );

    int readBufferedAutoCompResult(  );

    void addBkndMeasureDataListener( BkndMeasureDataListener * param0 );

    void runNoUIAACWithCompensationOption( LPTSTR param0, bool param1, bool param2, bool param3, bool param4 );

    TrkDrvObjectArray * readBufferedStatusHistory(  );

    double readBufferedExternalTempSensor(  );

    MaterialTemperatureData * readBufferedMaterialTemperature(  );

    TrkDrvObjectArray * readBufferedDiagnosticHistory(  );

    void removeBkndMeasureDataListener( BkndMeasureDataListener * param0 );

    void addCommandCompleteListener( CommandCompleteListener * param0 );

public:
};

#endif /* __TRACKER_H__ */
