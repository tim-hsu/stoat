#include "stoatApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<stoatApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

stoatApp::stoatApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  stoatApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  stoatApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  stoatApp::registerExecFlags(_factory);
}

stoatApp::~stoatApp() {}

void
stoatApp::registerApps()
{
  registerApp(stoatApp);
}

void
stoatApp::registerObjects(Factory & factory)
{
    Registry::registerObjectsTo(factory, {"stoatApp"});
}

void
stoatApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"stoatApp"});

  /* Uncomment Syntax parameter and register your new production objects here! */
}

void
stoatApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
stoatApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
stoatApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
stoatApp__registerApps()
{
  stoatApp::registerApps();
}

extern "C" void
stoatApp__registerObjects(Factory & factory)
{
  stoatApp::registerObjects(factory);
}

extern "C" void
stoatApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  stoatApp::associateSyntax(syntax, action_factory);
}

extern "C" void
stoatApp__registerExecFlags(Factory & factory)
{
  stoatApp::registerExecFlags(factory);
}
