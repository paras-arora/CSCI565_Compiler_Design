				#include "llvm/ADT/Statistic.h"
				#include "llvm/IR/Module.h"

				#include "llvm/Analysis/CallGraphSCCPass.h"
				#include "llvm/Pass.h"
				#include "llvm/Support/raw_ostream.h"
				#include "llvm/IR/Instruction.h"
				#include "llvm/IR/Argument.h"
				#include "llvm/IR/Value.h"
				#include "llvm/IR/Function.h"
				#include "llvm/IR/Attributes.h"
				#include "llvm/IR/DebugInfo.h"
				#include "llvm/IR/LegacyPassManager.h"

using namespace llvm;

namespace {
	struct SemanticAnalysisPass : public FunctionPass {
		static char ID;
		SemanticAnalysisPass() : FunctionPass(ID) {}

		bool runOnFunction(Function &F) override {

			for (Function::iterator it = F.begin(); it !=F.end(); it++)
			{
				for (BasicBlock::iterator itBB = it->begin(); itBB!= it->end();itBB++)
				{
					if(isa<CallInst>(itBB))
					{
						const CallInst *itBB_callInst = dyn_cast<CallInst>(itBB);
						const Function *f = dyn_cast<const Function>(itBB_callInst->getCalledValue()->stripPointerCasts());

						if(!(f->isDeclaration()))
						{
							int numOfArgs = itBB_callInst->getNumArgOperands();
							int numOfParams = f->getFunctionType()->getNumParams();



							MDNode *mdn = itBB_callInst->getMetadata("dbg");
							DILocation di_l = DILocation(mdn);
							int line = di_l.getLineNumber();

				      						if(numOfParams != numOfArgs)  			// Checking for equal number pf parameters and arguments.
				      						{
				      							errs()<< "Errors in\n";
				      							errs() << "Function " << f->getName() << " call on line " << line << ": expected " << numOfArgs << " arguments but " << numOfArgs << " is/are present.\n";
				      						}
				      						else
				      						{
				      							for(int i=0;i< numOfArgs;i++)
				      							{
				      								int argType = itBB_callInst->getArgOperand(i)->getType()->getTypeID();
				      								Type *tempArg = itBB_callInst->getArgOperand(i)->getType();
				      								if(tempArg->isIntegerTy(8))
				      								{
				      									argType =100;
				      								}

				      								int paramType = f->getFunctionType()->getParamType(i)->getTypeID();
				      								Type *tempParam = f->getFunctionType()->getParamType(i);
				      								if(tempParam->isIntegerTy(8))
				      								{
				      									paramType =100;
				      								}

													if(argType != paramType )
													{
														if(paramType==14)
														{
															Type *ty= f->getFunctionType()->getParamType(i);
															PointerType *pTy = dyn_cast<PointerType>(ty);
															if(pTy != NULL)
															{
																ty = pTy->getElementType();
																paramType = ty->getTypeID();
																errs() << "Error:\n";
																errs() << "Function " << f->getName() << " call on line " << line << ": argument type mismatch. Expected ";
																if(paramType==12)
																{
																	errs()<< (pTy->getElementType()->getStructName()).data();
																}
																else
																{
																	if(pTy->getElementType()->isIntegerTy(8))
																		paramType=100;

																	typeName_print(paramType);	
																	errs()<<" *";
																}
																errs() << " but argument is of type ";

																typeName_print(argType);
																errs() << ".\n";
																continue;


															}
														}
														else if(argType==14)
														{
															Type *ty= itBB_callInst->getArgOperand(i)->getType();
															PointerType *pTy = dyn_cast<PointerType>(ty);
															if(pTy != NULL)
															{
																ty = pTy->getElementType();
																argType = ty->getTypeID();

																errs() << "Error:\n";
																errs() << "Function " << f->getName() << " call on line " << line << ": argument type mismatch. Expected ";
																typeName_print(paramType);

																errs() << " but argument is of type ";
																if(argType==12)
																{
																	errs()<< (pTy->getElementType()->getStructName()).data();
																}	
																else
																{
																	if(pTy->getElementType()->isIntegerTy(8))
																		argType=100;
																	typeName_print(argType);	
																	errs()<<" *";
																}
																errs() << ".\n";
																continue;

															}
														}
														if(argType==1 || argType==2 ||argType==3 || argType==10 || argType ==100)
														{
															if(paramType==1 || paramType==2 ||paramType==3 || paramType==10 ||paramType == 100)
															{
																errs() << "WARNING:\n";
															}
															else
															{
																errs() << "Error:\n";
															}
														}


														errs() << "Function " << f->getName() << " call on line " << line << ": argument type mismatch. Expected ";
														typeName_print(paramType);
														errs() << " but argument is of type ";
														typeName_print(argType);
														errs() << ".\n";
													}
			//		Code for when arguments and parameter are pointers(can be structure , pointrrs, array pointers.)
													else if(argType==paramType && argType==14)
													{
														
														Type *ty= f->getFunctionType()->getParamType(i);
														PointerType *pTy = dyn_cast<PointerType>(ty);

														Type *ty1= itBB_callInst->getArgOperand(i)->getType();
														PointerType *pTy1 = dyn_cast<PointerType>(ty1);

														if(pTy != NULL)
														{
															ty = pTy->getElementType();
															paramType = ty->getTypeID();
														}
														if(pTy1 != NULL)
														{
															ty1 = pTy1->getElementType();
															argType = ty1->getTypeID();
														}
														if(paramType==12 && argType==12)
														{
															if((pTy->getElementType()->getStructName()).data() != (pTy1->getElementType()->getStructName()).data())
															{
																errs() << "Error:\n";
																errs() << "Function " << f->getName() << " call on line " << line << ": argument type mismatch. Expected ";
																errs()<< (pTy->getElementType()->getStructName()).data();
																errs() << " but argument is of type ";
																errs()<< (pTy1->getElementType()->getStructName()).data();
																errs() << ".\n";
															} 
														}
														else if(paramType==12 || argType==12)
														{
															errs() << "Error:\n";
															errs() << "Function " << f->getName() << " call on line " << line << ": argument type mismatch. Expected ";
															if(paramType==12)
															{
																errs()<< (pTy->getElementType()->getStructName()).data();
															}
															else
															{
																if(pTy->getElementType()->isIntegerTy(8))
																	paramType=100;
																typeName_print(paramType);	
																errs()<<" *";	
															}

															errs() << " but argument is of type ";

															if(argType==12)
															{
																errs()<< (pTy1->getElementType()->getStructName()).data();
															}
															else
															{
																if(pTy1->getElementType()->isIntegerTy(8))
																	argType=100;
																typeName_print(argType);	
																errs()<<" *";	
															}
															errs() << ".\n";
														}
														else
														{
															if(pTy->getElementType()->isIntegerTy(8))
																	paramType=100;
															if(pTy1->getElementType()->isIntegerTy(8))
																	argType=100;
															if(argType==1 || argType==2 ||argType==3 || argType==10 || argType ==100)
															{
																if(paramType==1 || paramType==2 ||paramType==3 || paramType==10 ||paramType == 100)
																{

																	errs() << "WARNING:\n";
																}
																else
																{
																	errs() << "Error:\n";
																}
															}
															errs() << "Function " << f->getName() << " call on line " << line << ": argument type mismatch. Expected ";
															typeName_print(paramType);
															errs()<<" *";	
															errs() << " but argument is of type ";
															typeName_print(argType);
															errs()<<" *";	
															errs() << ".\n";
														}
													}									
												}
											}
										}
									}	
								}
							}

							return false;
						}

						void typeName_print(int type_id) {
							switch (type_id) {
								case 0:
								errs() << "void";
								break;
								case 1:
								errs() << "float(16 bit)";
								break;
								case 2:
								errs() << "float(32 bit)";
								break;
								case 3:
								errs() << "double";
								break;
								case 10:
								errs() << "int";
								break;
								case 11:
								errs() << "function";
								break;
								case 12:
								errs() << "struct";
								break;
								case 13:
								errs() << "array";
								break;
								case 14:
								errs() << "pointer";
								break;
								case 15:
								errs() << "vector";
								break;
								case 100:
								errs() << "char";
								break;
								default:
								errs() << "type unknown";
								break;
							}
						}
					};

				}

				char SemanticAnalysisPass::ID = 0;
				static RegisterPass<SemanticAnalysisPass> X("SemanticAnalysisPass", "Semantic Analysis Pass");