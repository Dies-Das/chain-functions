from ngsolve import *
import cf_comp

mesh = Mesh(unit_cube.GenerateMesh(maxh=0.2))
fes = H1(mesh, order=1)
gfu = GridFunction(fes)
gfu.Set(CoefficientFunction(x*x))
cf = cf_comp.CF_Comp(gfu, CoefficientFunction((0.5*x,0.5*y,0.5*z)))
cf2 = cf_comp.CF_Comp(grad(gfu),CoefficientFunction((0.5*x,0.5*y,0.5*z)))*grad(CoefficientFunction((0.5*x,0.5*y,0.5*z)))
print(Integrate(InnerProduct(cf,cf), mesh))
print(Integrate(InnerProduct(cf2,cf2), mesh))