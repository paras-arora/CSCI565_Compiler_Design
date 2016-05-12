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
	struct SemanticAnalysisPass1 : public CallGraphSCCPass {
		static char ID;

		SemanticAnalysisPass1() : CallGraphSCCPass(ID) {}

		bool runOnSCC(CallGraphSCC &SCC) override {
			static bool first = true;
			if (first == true) {
				errs() << "List of function calls:" << "\n";
				first = false;
			}

			CallGraphSCC::iterator it = SCC.begin();
			if ((*it)->getFunction()) {
				
				if (!((*it)->getFunction()->isDeclaration())) {
					
					FunctionType *ft = (*it)->getFunction()->getFunctionType();
					int num_args = ft->getNumParams();
					errs() << ((*it)->getFunction()->getName()) << "(";

						for (int i = 0; i < num_args; i++) {

							int paramType = ft->getParamType(i)->getTypeID();
							Type *tempParam = ft->getParamType(i);
							if(tempParam->isIntegerTy(8))
							{
								paramType =100;
							}


							if(paramType==14)
							{

								Type *ty = ft->getParamType(i);
								PointerType *pTy = dyn_cast<PointerType>(ty);

								if(pTy!=NULL)
								{
									ty = pTy->getElementType();
									paramType = ty->getTypeID();
									if(pTy->getElementType()->isIntegerTy(8))
										paramType=100;							
								}
									typeName_print(paramType);
									errs()<<" *";
							}						      
							else
							{
								typeName_print(paramType);
							}

							if(i<num_args-1)
								errs()<<", ";
							}

							CallGraph &cg = getAnalysis<CallGraphWrapperPass>().getCallGraph();
							CallGraphNode *cgn = cg[(*it)->getFunction()];
							errs() << "):" << (cgn->getNumReferences() - 1) << "\n";
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
		errs() << "float";
		break;
		case 2:
		errs() << "float";
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
void getAnalysisUsage(AnalysisUsage &AU) const {
	CallGraphSCCPass::getAnalysisUsage(AU);
}

};
} 

char SemanticAnalysisPass1::ID = 0;
static RegisterPass<SemanticAnalysisPass1> X("SemanticAnalysisPass1", "Function count with arguments");