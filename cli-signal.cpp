/**
 * CLI Signal messenger client
 * Copyright (c) 2021 andrey.ivanov@commandus.com
 * MIT license
 */
#include <iostream>
#include <cstring>
#include <fstream>

#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <errno.h>

#include "argtable3/argtable3.h"
#include "config-json.h"
#include "errlist.h"
#include "config-filename.h"
#include "utilstring.h"

const std::string progname = "cli-signal";
#define DEF_CONFIG_FILE_NAME ".cli-signal"
#define DEF_IDENTITY_STORAGE_NAME "identity.json"
#define DEF_GATEWAYS_STORAGE_NAME "gateway.json"
#define DEF_TIME_FORMAT "%FT%T"

#define DEF_BUFFER_SIZE 4096
#define DEF_BUFFER_SIZE_S "4096"

static Configuration *config = NULL;

static void done()
{
	// destroy and free all
	if (config && config->serverConfig.verbosity > 1)
		std::cerr << MSG_GRACEFULLY_STOPPED << std::endl;
	exit(0);
}

static void stop()
{
}

void signalHandler(int signal)
{
	switch (signal)
	{
	case SIGINT:
		std::cerr << MSG_INTERRUPTED << std::endl;
		stop();
		done();
		break;
	default:
		break;
	}
}

#ifdef _MSC_VER
// TODO
void setSignalHandler()
{
}
#else
void setSignalHandler()
{
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = &signalHandler;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGHUP, &action, NULL);
}
#endif

/**
 * Parse command line
 * Return 0- success
 *        1- show help and exit, or command syntax error
 *        2- output file does not exists or can not open to write
 **/
int parseCmd(
	Configuration *config,
	int argc,
	char *argv[])
{
	// device path
	struct arg_str *a_address4 = arg_strn(NULL, NULL, "<IPv4 address:port>", 0, 8, "listener IPv4 interface e.g. *:8003");
	struct arg_str *a_address6 = arg_strn("6", "ipv6", "<IPv6 address:port>", 0, 8, "listener IPv6 interface e.g. :1700");
	struct arg_str *a_config = arg_str0("c", "config", "<file>", "configuration file. Default ~/" DEF_CONFIG_FILE_NAME ", stotage ~/" DEF_IDENTITY_STORAGE_NAME ", gateways ~/" DEF_GATEWAYS_STORAGE_NAME );

	struct arg_str *a_logfilename = arg_str0("l", "logfile", "<file>", "log file");
	struct arg_lit *a_daemonize = arg_lit0("d", "daemonize", "run daemon");
	struct arg_lit *a_verbosity = arg_litn("v", "verbose", 0, 3, "Set verbosity level");
	struct arg_lit *a_help = arg_lit0("?", "help", "Show this help");
	struct arg_end *a_end = arg_end(20);

	void *argtable[] = {
		a_config,
		a_address4, a_address6,
		a_logfilename, a_daemonize, a_verbosity, a_help, a_end};

	int nerrors;

	// verify the argtable[] entries were allocated successfully
	if (arg_nullcheck(argtable) != 0)
	{
		arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
		return 1;
	}
	// Parse the command line as defined by argtable[]
	nerrors = arg_parse(argc, argv, argtable);

	if (a_config->count)
		config->configFileName = *a_config->sval;
	else
		config->configFileName = getDefaultConfigFileName(DEF_CONFIG_FILE_NAME);

	config->serverConfig.daemonize = (a_daemonize->count > 0);
	config->serverConfig.verbosity = a_verbosity->count;

	if (!nerrors)
	{
		for (int i = 0; i < a_address4->count; i++)
		{
			config->serverConfig.listenAddressIPv4.push_back(a_address4->sval[i]);
		}
		for (int i = 0; i < a_address6->count; i++)
		{
			config->serverConfig.listenAddressIPv6.push_back(a_address6->sval[i]);
		}
	}

	// special case: '--help' takes precedence over error reporting
	if ((a_help->count) || nerrors)
	{
		if (nerrors)
			arg_print_errors(stderr, a_end, progname.c_str());
		std::cerr << "Usage: " << progname << std::endl;
		arg_print_syntax(stderr, argtable, "\n");
		std::cerr << MSG_PROG_NAME << std::endl;
		arg_print_glossary(stderr, argtable, "  %-25s %s\n");
		arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
		return ERR_CODE_HELP_REQUESTED;
	}

	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
	return 0;
}

void onLog(
	int level,
	int modulecode,
	int errorcode,
	const std::string &message
)
{
	std::cerr << message << std::endl;
}

int main(
	int argc,
	char *argv[])
{
	config = new Configuration("");
	if (parseCmd(config, argc, argv) != 0)
	{
		exit(ERR_CODE_COMMAND_LINE);
	}
	if (!config->configFileName.empty())
	{
		std::string js = file2string(config->configFileName.c_str());
		if (!js.empty())
		{
			config->parse(js.c_str());
		}
	}
	if (config->serverConfig.identityStorageName.empty()) {
		config->serverConfig.identityStorageName = getDefaultConfigFileName(DEF_IDENTITY_STORAGE_NAME);
	}
	if (config->gatewaysFileName.empty()) {
		config->gatewaysFileName = getDefaultConfigFileName(DEF_GATEWAYS_STORAGE_NAME);
	}
	std::cerr << config->toString() << std::endl;

#ifdef _MSC_VER
#else
	setSignalHandler();
#endif
	done();
	return 0;
}
