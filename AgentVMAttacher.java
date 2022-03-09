import com.sun.tools.attach.VirtualMachine;

public class AgentVMAttacher {
    public static void main(String[] args) throws Exception {
        String pid = args[0];
        String agentPath = "/home/tenghuanhe/agent/libattach_agent.so";
        VirtualMachine vm = com.sun.tools.attach.VirtualMachine.attach(pid);
        vm.loadAgentPath(agentPath, null);
        vm.detach();
    }
}
