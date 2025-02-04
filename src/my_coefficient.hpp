#ifndef MY_COEFFICIENT
#define MY_COEFFICIENT

#include <coefficient.hpp>
#include <gridfunction.hpp>

namespace ngfem
{
  
  /*
    CoefficientFunction which computes the eigenvalues of
    a symmetric 2x2 matrix-valued CoefficientFunction
  */
  class CF_Comp : public CoefficientFunction
  {
    // f is the grid function and g the transformation
    shared_ptr<ngcomp::GridFunctionCoefficientFunction> f;  
    shared_ptr<CoefficientFunction> g;  

  public:
    // Constructor: note that we inherit the dimension and height from f.
    CF_Comp (const shared_ptr<ngcomp::GridFunctionCoefficientFunction> & af, 
             const shared_ptr<CoefficientFunction> & ag)
      : CoefficientFunction(af->Dimension()), f(af), g(ag)
    { ; }

    // The Evaluate routine: given an integration point mip (with global point x)
    // it computes new_coords = g(x), then finds the element of f's mesh that
    // contains new_coords, and finally evaluates f there.
    double Evaluate(const BaseMappedIntegrationPoint & ip) const{
      throw Exception("wrong evaluate");
      return 0.0;
    }
    void Evaluate (const BaseMappedIntegrationPoint & mip,
                           FlatVector<double> res) const override
    {
      // First, compute y = g(x)
      LocalHeapMem<10000> lh2 ("GF_Comp, Eval");
      cout << "mip is " << mip << endl;
      int gd = g->Dimension();
      Vector new_coords(gd);
      g->Evaluate(mip, new_coords);
      cout << "trafo coords are: " << new_coords << endl;
      // Create a new IntegrationPoint whose global coordinates are the transformed ones.
      // MappedIntegrationPoint<3,3> tip;
      
      
      // We expect f to be a GridFunction. In that case, we can perform a mesh search.
      

      // Get the finite element space and the mesh access object.
      // f->GetGridFunctionPtr
      const auto fes = f->GetGridFunctionPtr()->GetFESpace();
      const auto & ma = fes->GetMeshAccess();
      IntegrationPoint tip(new_coords[0], new_coords[1], new_coords[2]);
      cout << "tip is " << tip << endl;
      // f->Evaluate()
      // auto res = ma->FindElementOfPoint();
      // Find the element in which tip.x lies. The call below should also update 'tip'
      // with the correct local coordinates. (The actual method name may vary with NGsolve version.)
      auto elnr = ma->FindElementOfPoint(tip.Point(), tip,false,0);
      std::cout << "elnr is " << elnr;
      if (elnr.IsInvalid()){
        // throw Exception("el not in mesh");
        // cout << "el not in mesh, mip is " << mip.GetPoint() << endl;
        ConstantCoefficientFunction(1).Evaluate(mip,res);
        return;}
      cout << "computing mip2" << endl;
      MappedIntegrationPoint<3,3> mip2(tip,ma->GetTrafo(elnr, lh2));
      cout << "mip2 is " << mip2;
      // Now evaluate the grid function f at the found element and local coordinates.
      f->Evaluate(mip2,res);
    }
    

  };
}



#endif

