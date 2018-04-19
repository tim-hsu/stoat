//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "stoatTestApp.h"
#include "stoatApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<stoatTestApp>()
{
  InputParameters params = validParams<stoatApp>();
  return params;
}

stoatTestApp::stoatTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  stoatApp::registerObjectDepends(_factory);
  stoatApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  stoatApp::associateSyntaxDepends(_syntax, _action_factory);
  stoatApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  stoatApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    stoatTestApp::registerObjects(_factory);
    stoatTestApp::associateSyntax(_syntax, _action_factory);
    stoatTestApp::registerExecFlags(_factory);
  }
}

stoatTestApp::~stoatTestApp() {}

void
stoatTestApp::registerApps()
{
  registerApp(stoatApp);
  registerApp(stoatTestApp);
}

void
stoatTestApp::registerObjects(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new test objects here! */
}

void
stoatTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new test objects here! */
}

void
stoatTestApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execute flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
stoatTestApp__registerApps()
{
  stoatTestApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
stoatTestApp__registerObjects(Factory & factory)
{
  stoatTestApp::registerObjects(factory);
}

// External entry point for dynamic syntax association
extern "C" void
stoatTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  stoatTestApp::associateSyntax(syntax, action_factory);
}

// External entry point for dynamic execute flag loading
extern "C" void
stoatTestApp__registerExecFlags(Factory & factory)
{
  stoatTestApp::registerExecFlags(factory);
}
