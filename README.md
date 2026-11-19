flowchart LR
    U[Team member] -->|prompt| G[CyberSyn]
    G --> S[3 local scanners]
    S --> D{Policy}
    D -->|allow / redact| P[AI provider]
    D -->|warn / block| U
    P -->|answer| U
