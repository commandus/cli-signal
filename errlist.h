
/* syslog
#define	LOG_ERROR							1
#define	LOG_INFO							2
#define	LOG_DEBUG							3
*/

#define LOG_UDP_EMITTER						1
#define LOG_UDP_LISTENER					2
#define LOG_IDENTITY_SVC					3
#define LOG_PACKET_HANDLER					4

#define SIGNAL_OK          					0
#define ERR_CODE_INSUFFICIENT_MEMORY		-500
#define ERR_CODE_COMMAND_LINE		    	-501
#define ERR_CODE_OPEN       		    	-502
#define ERR_CODE_CLOSE      		    	-503
#define ERR_CODE_BAD_STATUS		        	-504
#define ERR_CODE_WRONG_PARAM				-505
#define ERR_CODE_INSUFFICIENT_PARAMS		-506
#define ERR_CODE_NO_CONFIG					-507
#define ERR_CODE_HELP_REQUESTED             -508

#define ERR_MESSAGE						"Error "
#define ERR_DEBUG						"Info "
#define ERR_WARNING						"Warning "
#define ERR_TIMEOUT						"Timeout"

#define ERR_INSUFFICIENT_MEMORY			"Insufficient memory"
#define ERR_COMMAND_LINE        		"Wrong parameter(s)"
#define ERR_OPEN                 		"open error "
#define ERR_CLOSE               		"close error "
#define ERR_BAD_STATUS          		"Bad status"
#define ERR_WRONG_PARAM 				"Invalid parameter"
#define ERR_INSUFFICIENT_PARAMS			"Insufficient parameters"
#define ERR_NO_CONFIG					"No config is provided"
#define ERR_HELP_REQUESTED  			"Help requested"

#define MSG_PROG_NAME					"Signal CLI client"
#define MSG_INTERRUPTED 				MSG_PROG_NAME " interrupted "
#define MSG_GRACEFULLY_STOPPED			MSG_PROG_NAME " closed gracefully"
#define MSG_TIMEOUT						"Timeout"
#define MSG_STOPPED						"stopped gracefully"
#define MSG_RECEIVED					"Message received "

#define ERROR							"Error "

const char *strerror_client(int errcode);
